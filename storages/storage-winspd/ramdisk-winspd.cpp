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

    MStorage::Volume(_bufferDevice->volumeName()).format(MStorage::VolumeInfo::FileSystem::FAT32, QCoreApplication::applicationName(), false);

    MOperatingSystem::Settings::Device::AutoPlayHolder autoPlayHolder(false);

    _mountPoint = _parameters.drive + '\\';
    if (!SetVolumeMountPoint(_mountPoint.toLPCWStr(), MString(_bufferDevice->volumeName() + '\\').toLPCWStr()))
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