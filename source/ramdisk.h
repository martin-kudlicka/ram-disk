#ifndef RAMDISK_H
#define RAMDISK_H

#include "ramdiskoptions.h"
#include "../common/ramdiskinterface.h"

class RamDisk
{
  public:
     RamDisk(const MUuidPtr &id);
    ~RamDisk();

    RamDiskOptions &options();
    bool            running() const;
    void            start  ();
    void            stop   ();

  private:
    RamDiskInterfaceSPtr _ramDisk;
    RamDiskOptions       _options;
};

using RamDiskSPtr = QSharedPointer<RamDisk>;

#endif