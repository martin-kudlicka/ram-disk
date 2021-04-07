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
  catch (const MException::MCritical &ex)
  {
    _bufferDevice.reset();

    throw MException::MCritical(WinSpd(), ex.error(), ex.what());
  }

  try
  {
    auto volumesBefore = MVolumes::enumerate();

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

    QStringList volumesAfter;
    for (auto run = 0; run < 10; ++run)
    {
      QThread::msleep(100);

      volumesAfter = MVolumes::enumerate();
      if (volumesAfter.count() > volumesBefore.count())
      {
        break;
      }
    }

    if (volumesBefore.count() + 1 != volumesAfter.count())
    {
      throw MException::MCritical(WinSpd(), ERROR_MOUNT_POINT_NOT_RESOLVED, "can't find created ram disk volume");
    }

    auto newVolume = std::find_if_not(volumesAfter.cbegin(), volumesAfter.cend(), [&volumesBefore](const QString &volumeName)
    {
      return volumesBefore.contains(volumeName);
    });

    MStorage::Volume::format(*newVolume, MVolume::FileSystem::FAT32, QCoreApplication::applicationName(), false);

    auto autoPlayEnabled      = MOperatingSystem::Settings::Device::AutoPlay::enabled();
    auto autoPlayEnabledGuard = qScopeGuard([autoPlayEnabled] { MOperatingSystem::Settings::Device::AutoPlay::setEnabled(autoPlayEnabled); });
    if (autoPlayEnabled)
    {
      MOperatingSystem::Settings::Device::AutoPlay::setEnabled(false);
    }
    else
    {
      autoPlayEnabledGuard.dismiss();
    }

    _mountPoint = _parameters.drive + '\\';
    if (!SetVolumeMountPoint(_mountPoint.toStdWString().c_str(), (*newVolume + '\\').toStdWString().c_str()))
    {
      throw MException::MCritical(WinSpd(), GetLastError(), "SetVolumeMountPoint");
    }

    if (autoPlayEnabled)
    {
      QThread::msleep(200); // wait a little for system autoplay notifier
    }
  }
  catch (const MException::MCritical &)
  {
    _bufferDevice.reset();

    throw;
  }
}

void RamDiskWinSpd::stop()
{
  DeleteVolumeMountPointW(_mountPoint.toStdWString().c_str());

  _mountPoint.clear();
  _bufferDevice.reset();
}