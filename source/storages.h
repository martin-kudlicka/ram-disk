#ifndef STORAGES_H
#define STORAGES_H

#include "../storages/storageinterface.h"

class StoragesPlugins : public MPluginContainer<StorageInterface>
{
  public:
           StoragesPlugins();
  virtual ~StoragesPlugins() Q_DECL_EQ_DEFAULT;
};

extern MLazySingleton<StoragesPlugins> gStorages;

#endif