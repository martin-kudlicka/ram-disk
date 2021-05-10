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
    _bufferDevice->open(QIODevice::ReadWrite);

    mInfoC(WinSpd) << "RAM disk volume " << _bufferDevice->volumeName() << " created";

    MStorage::Volume(_bufferDevice->volumeName()).format(MStorage::VolumeInfo::FileSystem::FAT32, QCoreApplication::applicationName(), false);

    mInfoC(WinSpd) << "RAM disk volume " << _bufferDevice->volumeName() << " formatted to FAT32";

    _bufferDevice->mount({ _parameters.drive + '\\' });

    mInfoC(WinSpd) << "RAM disk volume " << _bufferDevice->volumeName() << " mounted to " << _parameters.drive;
  }
  catch (const MException::Critical &)
  {
    _bufferDevice.reset();

    throw;
  }
}

void RamDiskWinSpd::stop()
{
  _bufferDevice->unmount();

  mInfoC(WinSpd) << "RAM disk volume " << _bufferDevice->volumeName() << " unmounted from " << _parameters.drive;

  auto ramDiskVolumeName = _bufferDevice->volumeName();

  _mountPoint.clear();
  _bufferDevice.reset();

  mInfoC(WinSpd) << "RAM disk volume " << ramDiskVolumeName << " closed";
}