#include "pch.h"
#include "storage-winspd.h"

#include "ramdisk-winspd.h"

RamDiskInterfaceSPtr StorageWinSpd::create(const RamDiskParameters &parameters) const
{
  return QSharedPointer<RamDiskWinSpd>::create(parameters);
}

QString StorageWinSpd::name() const
{
  return "WinSpd";
}