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

    _bufferDevice->open(QIODevice::ReadWrite);

    QStringList volumesAfter;
    for (auto run = 0; run < 10; ++run)
    {
      Sleep(100);

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

    MStorage::format(*newVolume, MVolume::FileSystem::FAT32, QCoreApplication::applicationName(), false);

    _mountPoint = _parameters.drive + '\\';
    if (!SetVolumeMountPoint(_mountPoint.toStdWString().c_str(), (*newVolume + '\\').toStdWString().c_str()))
    {
      throw MException::MCritical(WinSpd(), GetLastError(), "SetVolumeMountPoint");
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