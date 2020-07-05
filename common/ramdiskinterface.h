#ifndef RAMDISKINTERFACE_H
#define RAMDISKINTERFACE_H

#include "ramdiskparameters.h"

class RamDiskInterface
{
  public:
    RamDiskInterface(const RamDiskParameters &parameters) : _parameters(parameters)
    {
    }

    virtual bool start()       = 0;
    virtual bool stop () const = 0;

  protected:
    RamDiskParameters _parameters;
};

using RamDiskInterfaceSPtr = QSharedPointer<RamDiskInterface>;

#endif