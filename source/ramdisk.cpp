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

bool RamDisk::start()
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
    mCriticalC(RAMDisk) << "RAM disk storage \"" << _options.storage() << "\" unavailable";

    return false;
  }

  try
  {
    _ramDisk->start();

    mInfoC(RAMDisk) << "RAM disk \"" << _options.drive() << "\" started";
  }
  catch (const MException::MCritical &ex)
  {
    mCriticalEx(ex);
    mCriticalC(RAMDisk) << "RAM disk \"" << _options.drive() << "\" failed to start";

    _ramDisk.clear();

    return false;
  }

  return true;
}

void RamDisk::stop()
{
  _ramDisk->stop();

  mInfoC(RAMDisk) << "RAM disk \"" << _options.drive() << "\" stopped";

  _ramDisk.clear();
}