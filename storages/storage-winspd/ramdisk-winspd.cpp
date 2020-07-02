#include "pch.h"
#include "ramdisk-winspd.h"

#include "storageunitinterface.h"
#include "rawdisk.h"

RamDiskWinSpd::RamDiskWinSpd(const RamDiskParameters &parameters) : RamDiskInterface(parameters)
{
}

bool RamDiskWinSpd::start() const
{
  SPD_STORAGE_UNIT_PARAMS storageUnitParams = {};

  UuidCreate(&storageUnitParams.Guid);
  storageUnitParams.BlockCount  = _parameters.size * 1024 * 1024 / 4096;
  storageUnitParams.BlockLength = 4096;
  lstrcpyA(reinterpret_cast<LPSTR>(storageUnitParams.ProductId),            "RAM Disk");
  lstrcpyA(reinterpret_cast<LPSTR>(storageUnitParams.ProductRevisionLevel), "0.1");
  storageUnitParams.WriteProtected    = TRUE;
  //storageUnitParams.CacheSupported    = FALSE;
  //storageUnitParams.UnmapSupported    = FALSE;
  storageUnitParams.MaxTransferLength = 64 * 1024;

  auto rawDisk = new RawDisk();
  rawDisk->parameters = _parameters;
  rawDisk->data       = static_cast<LPBYTE>(malloc(_parameters.size));

  if (rawDisk->data)
  {
    SPD_STORAGE_UNIT *storageUnit = nullptr;
    auto error = SpdStorageUnitCreate(nullptr, &storageUnitParams, &gStorageUnitInterface, &storageUnit);
    if (error == ERROR_SUCCESS)
    {
      rawDisk->storageUnit = storageUnit;

      storageUnit->UserContext = rawDisk;

      return true;
    }
  }

  delete rawDisk;

  return false;
}

bool RamDiskWinSpd::stop() const
{
  // TODO

  return true;
}