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
    mCCritical(RAMDisk) << "RAM disk storage \"" << _options.storage() << "\" unavailable";

    return;
  }

  auto ok = _ramDisk->start();
  if (ok)
  {
    mCInfo(RAMDisk) << "RAM disk \"" << _options.drive() << "\" started";
  }
  else
  {
    mCCritical(RAMDisk) << "RAM disk \"" << _options.drive() << "\" failed to start";

    _ramDisk.clear();
  }
}

void RamDisk::stop()
{
  _ramDisk->stop();

  mCInfo(RAMDisk) << "RAM disk \"" << _options.drive() << "\" stopped";

  _ramDisk.clear();
}