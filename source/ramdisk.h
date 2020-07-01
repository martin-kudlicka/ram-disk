#ifndef RAMDISK_H
#define RAMDISK_H

#include "ramdiskoptions.h"
#include "../common/ramdiskinterface.h"

class RamDisk
{
  public:
    RamDisk(const MUuidPtr &id);

    RamDiskOptions &options();
    void            start  ();
    void            stop   ();

  private:
    RamDiskInterfaceSPtr _disk;
    RamDiskOptions       _options;
};

using RamDiskSPtr = QSharedPointer<RamDisk>;

#endif