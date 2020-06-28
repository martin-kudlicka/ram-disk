#include "pch.h"
#include "disk.h"

Disk::Disk(const MUuidPtr &id) : _options(id)
{
}

DiskOptions &Disk::options()
{
  return _options;
}