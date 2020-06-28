#ifndef STORAGEINTERFACE_H
#define STORAGEINTERFACE_H

#include <QtCore/QObject>

class MUuidPtr;

#define IID_STORAGEINTERFACE "cz.martink.RAMDisk.StorageInterface"

class StorageInterface : public QObject
{
  Q_OBJECT

  public:
    virtual QString name() = 0;
    virtual void start  () = 0;
    virtual void stop   () = 0;
};

Q_DECLARE_INTERFACE(StorageInterface, IID_STORAGEINTERFACE);

#endif