#ifndef STORAGEWINSPD_H
#define STORAGEWINSPD_H

#include "../storageinterface.h"

class StorageWinSpd : public StorageInterface
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID IID_STORAGEINTERFACE)
  Q_INTERFACES(StorageInterface)

  private:
    virtual ~StorageWinSpd() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    virtual RamDiskInterfaceSPtr create(const RamDiskParameters &parameters) const;
    virtual QString              name  ()                                    const;
};

#endif