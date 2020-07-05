#include "pch.h"
#include "ramdisk-winspd.h"

#include "storageunitinterface.h"

RamDiskWinSpd::RamDiskWinSpd(const RamDiskParameters &parameters) : RamDiskInterface(parameters), _storageUnit(nullptr)
{
}

bool RamDiskWinSpd::start()
{
  auto sizeInBytes = _parameters.size * 1024 * 1024;

  SPD_STORAGE_UNIT_PARAMS storageUnitParams = {};

  UuidCreate(&storageUnitParams.Guid);
  storageUnitParams.BlockCount  = sizeInBytes / 4096;
  storageUnitParams.BlockLength = 4096;
  lstrcpyA(reinterpret_cast<LPSTR>(storageUnitParams.ProductId),            "RAM Disk");
  lstrcpyA(reinterpret_cast<LPSTR>(storageUnitParams.ProductRevisionLevel), "0.1");
  storageUnitParams.WriteProtected    = TRUE;
  //storageUnitParams.CacheSupported    = FALSE;
  //storageUnitParams.UnmapSupported    = FALSE;
  storageUnitParams.MaxTransferLength = 64 * 1024;

  _data.resize(sizeInBytes);
  if (static_cast<quintptr>(_data.size()) == sizeInBytes)
  {
    auto error = SpdStorageUnitCreate(nullptr, &storageUnitParams, &gStorageUnitInterface, &_storageUnit);
    if (error == ERROR_SUCCESS)
    {
      _storageUnit->UserContext = this;

      return true;
    }
  }

  return false;
}

bool RamDiskWinSpd::stop() const
{
  // TODO

  return true;
}