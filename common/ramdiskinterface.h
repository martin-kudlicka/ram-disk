#ifndef RAMDISKINTERFACE_H
#define RAMDISKINTERFACE_H

#include "ramdiskparameters.h"

class RamDiskInterface
{
  public:
    RamDiskInterface(const RamDiskParameters &parameters) : _parameters(parameters)
    {
    }

    virtual void start() = 0;
    virtual void stop () = 0;

  protected:
    RamDiskParameters _parameters;
};

using RamDiskInterfaceSPtr = QSharedPointer<RamDiskInterface>;

#endif