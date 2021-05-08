#include "pch.h"
#include "ramdisk-winspd.h"

#include "log.h"

RamDiskWinSpd::RamDiskWinSpd(const RamDiskParameters &parameters) : RamDiskInterface(parameters)
{
}

void RamDiskWinSpd::start()
{
  _bufferDevice.reset(new MWinSpdBufferDevice());

  try
  {
    _bufferDevice->setSize(_parameters.size * 1024 * 1024);
  }
  catch (const MException::Critical &ex)
  {
    _bufferDevice.reset();

    throw MException::Critical(WinSpd(), ex.error(), ex.what());
  }

  try
  {
    auto volumesBefore = MStorage::Volume::enumerate();

    {
      // automount has to be enabled otherwise format fails
      auto automountEnabled      = MStorage::Automount::enabled();
      auto automountEnabledGuard = qScopeGuard([automountEnabled] { MStorage::Automount::setEnabled(automountEnabled); });
      if (!automountEnabled)
      {
        MStorage::Automount::setEnabled(true);
      }
      else
      {
        automountEnabledGuard.dismiss();
      }

      _bufferDevice->open(QIODevice::ReadWrite);
    }

    MStorage::VolumeInfoList volumesAfter;
    for (auto run = 0; run < 10; ++run)
    {
      QThread::msleep(100);

      volumesAfter = MStorage::Volume::enumerate();
      if (volumesAfter.count() > volumesBefore.count())
      {
        break;
      }
    }
    if (volumesBefore.count() + 1 != volumesAfter.count())
    {
      throw MException::Critical(WinSpd(), ERROR_MOUNT_POINT_NOT_RESOLVED, "can't find created ram disk volume");
    }
    auto newVolume = std::find_if_not(volumesAfter.cbegin(), volumesAfter.cend(), [&volumesBefore](const MStorage::VolumeInfo &volumeAfter)
    {
      auto volume = std::find_if(volumesBefore.cbegin(), volumesBefore.cend(), [&volumeAfter](const MStorage::VolumeInfo &volumeBefore)
      {
        return volumeBefore.name() == volumeAfter.name();
      });

      return volume != volumesBefore.cend();
    });

    MStorage::Volume(newVolume->name()).format(MStorage::VolumeInfo::FileSystem::FAT32, QCoreApplication::applicationName(), false);

    auto autoPlayHolder = MOperatingSystem::Settings::Device::AutoPlay().hold(false);

    _mountPoint = _parameters.drive + '\\';
    if (!SetVolumeMountPoint(_mountPoint.toLPCWStr(), MString(newVolume->name() + '\\').toLPCWStr()))
    {
      throw MException::Critical(WinSpd(), GetLastError(), "SetVolumeMountPoint");
    }
  }
  catch (const MException::Critical &)
  {
    _bufferDevice.reset();

    throw;
  }
}

void RamDiskWinSpd::stop()
{
  DeleteVolumeMountPointW(_mountPoint.toLPCWStr());

  _mountPoint.clear();
  _bufferDevice.reset();
}