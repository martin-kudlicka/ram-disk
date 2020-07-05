#include "pch.h"
#include "storageunitinterface.h"

#include "ramdisk-winspd.h"

typedef struct _RAWDISK
{
  SPD_STORAGE_UNIT *StorageUnit;
  UINT64 BlockCount;
  UINT32 BlockLength;
  HANDLE Handle;
  HANDLE Mapping;
  PVOID Pointer;
  BOOLEAN Sparse;
} RAWDISK;

BOOLEAN FlushInternal(SPD_STORAGE_UNIT *StorageUnit, UINT64 BlockAddress, UINT32 BlockCount, SPD_STORAGE_UNIT_STATUS *Status)
{
  Q_UNUSED(StorageUnit);
  Q_UNUSED(BlockAddress);
  Q_UNUSED(BlockCount);
  Q_UNUSED(Status);

  return TRUE;
}

BOOLEAN Read(SPD_STORAGE_UNIT *StorageUnit, PVOID Buffer, UINT64 BlockAddress, UINT32 BlockCount, BOOLEAN FlushFlag, SPD_STORAGE_UNIT_STATUS *Status)
{
  if (FlushFlag)
  {
    FlushInternal(StorageUnit, BlockAddress, BlockCount, Status);
    if (Status->ScsiStatus != SCSISTAT_GOOD)
    {
      return FALSE;
    }
  }

  auto ramDisk = static_cast<RamDiskWinSpd *>(StorageUnit->UserContext);

  return ramDisk->read(static_cast<LPCBYTE>(Buffer), BlockAddress, BlockCount, Status);
}

BOOLEAN Write(SPD_STORAGE_UNIT *StorageUnit, PVOID Buffer, UINT64 BlockAddress, UINT32 BlockCount, BOOLEAN FlushFlag, SPD_STORAGE_UNIT_STATUS *Status)
{
  auto ramDisk = static_cast<RamDiskWinSpd *>(StorageUnit->UserContext);

  auto ok = ramDisk->write(static_cast<LPBYTE>(Buffer), BlockAddress, BlockCount, Status);

  if (Status->ScsiStatus == SCSISTAT_GOOD && FlushFlag)
  {
    FlushInternal(StorageUnit, BlockAddress, BlockCount, Status);
  }

  return ok;
}

BOOLEAN Flush(SPD_STORAGE_UNIT *StorageUnit, UINT64 BlockAddress, UINT32 BlockCount, SPD_STORAGE_UNIT_STATUS *Status)
{
  return FlushInternal(StorageUnit, BlockAddress, BlockCount, Status);
}

BOOLEAN Unmap(SPD_STORAGE_UNIT *StorageUnit, SPD_UNMAP_DESCRIPTOR Descriptors[], UINT32 Count, SPD_STORAGE_UNIT_STATUS *Status)
{
  Q_UNUSED(StorageUnit);
  Q_UNUSED(Status);

  auto ramDisk = static_cast<RamDiskWinSpd *>(StorageUnit->UserContext);

  return ramDisk->unmap(Descriptors, Count);
}

SPD_STORAGE_UNIT_INTERFACE gStorageUnitInterface =
{
    Read,
    Write,
    Flush,
    Unmap,
};