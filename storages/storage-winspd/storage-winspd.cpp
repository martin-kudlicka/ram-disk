#include "pch.h"
#include "storage-winspd.h"

RamDiskInterfaceSPtr StorageWinSpd::create(const RamDiskParameters &parameters) const
{
  Q_UNUSED(parameters);

  // TODO

  return nullptr;
}

QString StorageWinSpd::name() const
{
  return "WinSpd";
}