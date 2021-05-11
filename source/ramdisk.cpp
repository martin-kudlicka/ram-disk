#include "pch.h"
#include "ramdisk.h"

#include "storages.h"
#include "log.h"

RamDisk::RamDisk(const MUuidPtr &id) : _options(id)
{
}

RamDisk::~RamDisk()
{
  if (_ramDisk)
  {
    stop();
  }
}

RamDiskOptions &RamDisk::options()
{
  return _options;
}

bool RamDisk::running() const
{
  return _ramDisk;
}

void RamDisk::start()
{
  for (const auto &storage : gStorages->toRawList())
  {
    if (storage->name() == _options.storage())
    {
      RamDiskParameters parameters;
      parameters.drive = _options.drive();
      parameters.size  = _options.size();

      _ramDisk = storage->create(parameters);

      break;
    }
  }
  if (!_ramDisk)
  {
    throw MException::Critical(RAMDisk(), "RAM disk storage \"" + _options.storage() + "\" unavailable");
  }

  try
  {
    _ramDisk->start();

    mInfoC(RAMDisk) << "RAM disk \"" << _options.drive() << "\" started";
  }
  catch (const MException::Critical &ex)
  {
    mCriticalEx(ex);

    _ramDisk.clear();

    throw;
  }
}

void RamDisk::stop()
{
  try
  {
    _ramDisk->stop();

    mInfoC(RAMDisk) << "RAM disk \"" << _options.drive() << "\" stopped";
  }
  catch (const MException::Critical &ex)
  {
    mCriticalEx(ex);
  }

  _ramDisk.clear();
}