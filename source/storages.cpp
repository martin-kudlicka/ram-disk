#include "pch.h"
#include "storages.h"

MLazySingleton<StoragesPlugins> gStorages;

StoragesPlugins::StoragesPlugins() : MPluginContainer<StorageInterface>("storage")
{
}