#ifndef STORAGEWINSPD_H
#define STORAGEWINSPD_H

#include "../storageinterface.h"

class StorageWinSpd : public StorageInterface
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID IID_STORAGEINTERFACE)
  Q_INTERFACES(StorageInterface)

  private:
    virtual QString name();
    virtual void start  ();
    virtual void stop   ();
};

#endif