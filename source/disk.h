#ifndef DISK_H
#define DISK_H

#include "diskoptions.h"

class Disk
{
  public:
    Disk(const MUuidPtr &id);

    DiskOptions &options();

  private:
    DiskOptions _options;
};

using DiskSPtr = QSharedPointer<Disk>;

#endif