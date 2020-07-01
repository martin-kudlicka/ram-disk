#include "pch.h"
#include "ramdisk.h"

#include "../common/ramdiskparameters.h"
#include "storages.h"
#include "log.h"

RamDisk::RamDisk(const MUuidPtr &id) : _options(id)
{
}

RamDiskOptions &RamDisk::options()
{
  return _options;
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

      _disk = storage->create(parameters);

      mCInfo(RAMDisk) << "RAM disk \"" << _options.drive() << "\" started";

      return;
    }
  }

  mCCritical(RAMDisk) << "RAM disk \"" << _options.drive() << "\" failed to start";
}

void RamDisk::stop()
{
  _disk.clear();

  mCInfo(RAMDisk) << "RAM disk \"" << _options.drive() << "\" stopped";
}