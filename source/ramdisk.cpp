#include "pch.h"
#include "ramdisk.h"

RamDisk::RamDisk(const MUuidPtr &id) : _options(id)
{
}

RamDiskOptions &RamDisk::options()
{
  return _options;
}