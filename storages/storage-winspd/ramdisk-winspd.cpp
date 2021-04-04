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
    _bufferDevice->open(QIODevice::ReadWrite);
  }
  catch (const MException::MCritical &)
  {
    _bufferDevice.reset();

    throw;
  }
}

void RamDiskWinSpd::stop()
{
  _bufferDevice.reset();
}