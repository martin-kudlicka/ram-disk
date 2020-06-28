#include "pch.h"
#include "ramdisk.h"

#include "../common/ramdiskparameters.h"
#include "storages.h"

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
      // TODO
      _disk = storage->create(parameters);
    }
  }

  // TODO
}

void RamDisk::stop()
{
  _disk.clear();
}