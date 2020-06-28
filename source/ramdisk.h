#ifndef RAMDISK_H
#define RAMDISK_H

#include "ramdiskoptions.h"

class RamDisk
{
  public:
    RamDisk(const MUuidPtr &id);

    RamDiskOptions &options();

  private:
    RamDiskOptions _options;
};

using DiskSPtr = QSharedPointer<RamDisk>;

#endif