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
  Q_UNUSED(Descriptors);
  Q_UNUSED(Count);
  Q_UNUSED(Status);

  /*WARNONCE(!StorageUnit->StorageUnitParams.WriteProtected);
  WARNONCE(StorageUnit->StorageUnitParams.UnmapSupported);

  RAWDISK *RawDisk = StorageUnit->UserContext;
  FILE_ZERO_DATA_INFORMATION Zero;
  DWORD BytesTransferred;
  PVOID FileBuffer;

  for (UINT32 I = 0; Count > I; I++)
  {
    BOOLEAN SetZero = FALSE;

    if (RawDisk->Sparse)
    {
      Zero.FileOffset.QuadPart = Descriptors[I].BlockAddress * RawDisk->BlockLength;
      Zero.BeyondFinalZero.QuadPart = (Descriptors[I].BlockAddress + Descriptors[I].BlockCount) *
        RawDisk->BlockLength;
      SetZero = DeviceIoControl(RawDisk->Handle,
                                FSCTL_SET_ZERO_DATA, &Zero, sizeof Zero, 0, 0, &BytesTransferred, 0);
    }

    if (!SetZero)
    {
      FileBuffer = (PUINT8)RawDisk->Pointer + Descriptors[I].BlockAddress * RawDisk->BlockLength;

      CopyBuffer(StorageUnit,
                 FileBuffer, 0, Descriptors[I].BlockCount * RawDisk->BlockLength, SCSI_ADSENSE_NO_SENSE,
                 0);
    }
  }*/

  return TRUE;
}

SPD_STORAGE_UNIT_INTERFACE gStorageUnitInterface =
{
    Read,
    Write,
    Flush,
    Unmap,
};