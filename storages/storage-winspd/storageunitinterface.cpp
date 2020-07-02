#include "pch.h"
#include "storageunitinterface.h"

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

BOOLEAN FlushInternal(SPD_STORAGE_UNIT *StorageUnit,
                             UINT64 BlockAddress, UINT32 BlockCount,
                             SPD_STORAGE_UNIT_STATUS *Status)
{
  Q_UNUSED(StorageUnit);
  Q_UNUSED(BlockAddress);
  Q_UNUSED(BlockCount);
  Q_UNUSED(Status);
  /*RAWDISK *RawDisk = StorageUnit->UserContext;
  PVOID FileBuffer = (PUINT8)RawDisk->Pointer + BlockAddress * RawDisk->BlockLength;

  if (!FlushViewOfFile(FileBuffer, BlockCount * RawDisk->BlockLength))
    goto error;
  if (!FlushFileBuffers(RawDisk->Handle))
    goto error;

  return TRUE;

  error:
  SpdStorageUnitStatusSetSense(Status,
                               SCSI_SENSE_MEDIUM_ERROR, SCSI_ADSENSE_WRITE_ERROR, 0);*/

  return TRUE;
}

BOOLEAN Read(SPD_STORAGE_UNIT *StorageUnit,
                    PVOID Buffer, UINT64 BlockAddress, UINT32 BlockCount, BOOLEAN FlushFlag,
                    SPD_STORAGE_UNIT_STATUS *Status)
{
  Q_UNUSED(StorageUnit);
  Q_UNUSED(Buffer);
  Q_UNUSED(BlockAddress);
  Q_UNUSED(BlockCount);
  Q_UNUSED(FlushFlag);
  Q_UNUSED(Status);

  /*WARNONCE(StorageUnit->StorageUnitParams.CacheSupported || FlushFlag);

  if (FlushFlag)
  {
    FlushInternal(StorageUnit, BlockAddress, BlockCount, Status);
    if (SCSISTAT_GOOD != Status->ScsiStatus)
      return TRUE;
  }

  RAWDISK *RawDisk = StorageUnit->UserContext;
  PVOID FileBuffer = (PUINT8)RawDisk->Pointer + BlockAddress * RawDisk->BlockLength;

  CopyBuffer(StorageUnit,
             Buffer, FileBuffer, BlockCount * RawDisk->BlockLength, SCSI_ADSENSE_UNRECOVERED_ERROR,
             Status);*/

  return TRUE;
}

BOOLEAN Write(SPD_STORAGE_UNIT *StorageUnit,
                     PVOID Buffer, UINT64 BlockAddress, UINT32 BlockCount, BOOLEAN FlushFlag,
                     SPD_STORAGE_UNIT_STATUS *Status)
{
  Q_UNUSED(StorageUnit);
  Q_UNUSED(Buffer);
  Q_UNUSED(BlockAddress);
  Q_UNUSED(BlockCount);
  Q_UNUSED(FlushFlag);
  Q_UNUSED(Status);

  /*WARNONCE(!StorageUnit->StorageUnitParams.WriteProtected);
  WARNONCE(StorageUnit->StorageUnitParams.CacheSupported || FlushFlag);

  RAWDISK *RawDisk = StorageUnit->UserContext;
  PVOID FileBuffer = (PUINT8)RawDisk->Pointer + BlockAddress * RawDisk->BlockLength;

  CopyBuffer(StorageUnit,
             FileBuffer, Buffer, BlockCount * RawDisk->BlockLength, SCSI_ADSENSE_WRITE_ERROR,
             Status);

  if (SCSISTAT_GOOD == Status->ScsiStatus && FlushFlag)
    FlushInternal(StorageUnit, BlockAddress, BlockCount, Status);*/

  return TRUE;
}

BOOLEAN Flush(SPD_STORAGE_UNIT *StorageUnit,
                     UINT64 BlockAddress, UINT32 BlockCount,
                     SPD_STORAGE_UNIT_STATUS *Status)
{
  /*WARNONCE(!StorageUnit->StorageUnitParams.WriteProtected);
  WARNONCE(StorageUnit->StorageUnitParams.CacheSupported);*/

  return FlushInternal(StorageUnit, BlockAddress, BlockCount, Status);
}

BOOLEAN Unmap(SPD_STORAGE_UNIT *StorageUnit,
                     SPD_UNMAP_DESCRIPTOR Descriptors[], UINT32 Count,
                     SPD_STORAGE_UNIT_STATUS *Status)
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