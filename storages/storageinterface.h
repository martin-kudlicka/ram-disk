#ifndef STORAGEINTERFACE_H
#define STORAGEINTERFACE_H

#include <QtCore/QObject>
#include "../common/ramdiskinterface.h"

struct RamDiskParameters;

class MUuidPtr;

#define IID_STORAGEINTERFACE "cz.martink.RAMDisk.StorageInterface"

class StorageInterface : public QObject
{
  Q_OBJECT

  public:
    virtual RamDiskInterfaceSPtr create(const RamDiskParameters &parameters) const = 0;
    virtual QString              name  ()                                    const = 0;

  protected:
    virtual ~StorageInterface() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

Q_DECLARE_INTERFACE(StorageInterface, IID_STORAGEINTERFACE);

#endif