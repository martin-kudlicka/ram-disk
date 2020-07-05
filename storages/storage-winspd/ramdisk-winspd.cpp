#include "pch.h"
#include "ramdisk-winspd.h"

#include "storageunitinterface.h"

auto BlockLength = 4096;

RamDiskWinSpd::RamDiskWinSpd(const RamDiskParameters &parameters) : RamDiskInterface(parameters), _storageUnit(nullptr)
{
}

bool RamDiskWinSpd::read(LPCBYTE source, quintptr blockAddress, quintptr blockCount, SPD_STORAGE_UNIT_STATUS *status)
{
  auto destination = _data.data() + blockAddress * BlockLength;

  return copyBuffer(source, destination, blockCount * BlockLength, SCSI_ADSENSE_UNRECOVERED_ERROR, status);
}

bool RamDiskWinSpd::unmap(const SPD_UNMAP_DESCRIPTOR *descriptors, quintptr count) const
{
  for (decltype(count) descriptorIndex = 0; descriptorIndex < count; ++descriptorIndex)
  {
    auto descriptor = &descriptors[descriptorIndex];

    BOOLEAN setZero = FALSE;

    /*if (false)
    {
      FILE_ZERO_DATA_INFORMATION Zero;
      DWORD BytesTransferred;

      Zero.FileOffset.QuadPart = descriptor->BlockAddress * BlockLength;
      Zero.BeyondFinalZero.QuadPart = (descriptor->BlockAddress + descriptor->BlockCount) * BlockLength;
      setZero = DeviceIoControl(RawDisk->Handle, FSCTL_SET_ZERO_DATA, &Zero, sizeof Zero, 0, 0, &BytesTransferred, 0);
    }*/

    if (!setZero)
    {
      auto source = _data.data() + descriptor->BlockAddress * BlockLength;

      copyBuffer(source, nullptr, descriptor->BlockCount * BlockLength, SCSI_ADSENSE_NO_SENSE, nullptr);
    }
  }

  return true;
}

bool RamDiskWinSpd::write(LPBYTE destination, quintptr blockAddress, quintptr blockCount, SPD_STORAGE_UNIT_STATUS *status) const
{
  auto source = _data.data() + blockAddress * BlockLength;

  return copyBuffer(source, destination, blockCount * BlockLength, SCSI_ADSENSE_WRITE_ERROR, status);
}

bool RamDiskWinSpd::copyBuffer(LPCBYTE source, LPBYTE destination, quintptr size, quint8 senseCode, SPD_STORAGE_UNIT_STATUS *status) const
{
  quintptr exceptionDataAddress = 0;

  __try
  {
    if (source)
    {
      memcpy(destination, source, size);
    }
    else
    {
      memset(destination, 0, size);
    }
  }
  __except (exceptionFilter(GetExceptionCode(), GetExceptionInformation(), &exceptionDataAddress))
  {
    if (status)
    {
      quint64 exceptionInformation;
      quint64 *exceptionInformationPtr = nullptr;
      if (exceptionDataAddress)
      {
        exceptionInformation    = (exceptionDataAddress - reinterpret_cast<quintptr>(_data.data())) / BlockLength;
        exceptionInformationPtr = &exceptionInformation;
      }

      SpdStorageUnitStatusSetSense(status, SCSI_SENSE_MEDIUM_ERROR, senseCode, exceptionInformationPtr);
    }

    return false;
  }

  return true;
}

bool RamDiskWinSpd::start()
{
  auto sizeInBytes = _parameters.size * 1024 * 1024;

  SPD_STORAGE_UNIT_PARAMS storageUnitParams = {};

  UuidCreate(&storageUnitParams.Guid);
  storageUnitParams.BlockCount  = sizeInBytes / BlockLength;
  storageUnitParams.BlockLength = BlockLength;
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

void RamDiskWinSpd::stop()
{
  SpdStorageUnitDelete(_storageUnit);

  _data.clear();
}

BOOLEAN RamDiskWinSpd::exceptionFilter(DWORD code, PEXCEPTION_POINTERS pointers, quintptr *dataAddress)
{
  if (code != EXCEPTION_IN_PAGE_ERROR)
  {
    return EXCEPTION_CONTINUE_SEARCH;
  }

  *dataAddress = 2 <= pointers->ExceptionRecord->NumberParameters ? pointers->ExceptionRecord->ExceptionInformation[1] : 0;

  return EXCEPTION_EXECUTE_HANDLER;
}