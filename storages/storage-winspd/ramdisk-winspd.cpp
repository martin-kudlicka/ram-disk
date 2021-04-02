#include "pch.h"
#include "ramdisk-winspd.h"

#include "log.h"
#include "storageunitinterface.h"

auto BlockLength = 4096;

RamDiskWinSpd::RamDiskWinSpd(const RamDiskParameters &parameters) : RamDiskInterface(parameters), _storageUnit(nullptr)
{
}

bool RamDiskWinSpd::read(LPBYTE destination, quintptr blockAddress, quintptr blockCount, SPD_STORAGE_UNIT_STATUS *status) const
{
  auto source = _data.data() + blockAddress * BlockLength;

  return copyBuffer(source, destination, blockCount * BlockLength, SCSI_ADSENSE_UNRECOVERED_ERROR, status);
}

bool RamDiskWinSpd::unmap(const SPD_UNMAP_DESCRIPTOR *descriptors, quintptr count)
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
      auto destination = _data.data() + descriptor->BlockAddress * BlockLength;

      copyBuffer(nullptr, destination, descriptor->BlockCount * BlockLength, SCSI_ADSENSE_NO_SENSE, nullptr);
    }
  }

  return true;
}

bool RamDiskWinSpd::write(LPCBYTE source, quintptr blockAddress, quintptr blockCount, SPD_STORAGE_UNIT_STATUS *status)
{
  auto destination = _data.data() + blockAddress * BlockLength;

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

void RamDiskWinSpd::start()
{
  auto sizeInBytes = _parameters.size * 1024 * 1024;

  static auto productId = []
  {
    auto val = QCoreApplication::applicationName();
    val.truncate(_countof(SPD_STORAGE_UNIT_PARAMS::ProductId));
    return val;
  }();
  static auto revision  = []
  {
    auto val = QCoreApplication::applicationVersion();
    val.remove('.');
    while (val.startsWith('0'))
    {
      val.remove(0, 1);
    }
    val.truncate(_countof(SPD_STORAGE_UNIT_PARAMS::ProductRevisionLevel));
    return val;
  }();

  SPD_STORAGE_UNIT_PARAMS storageUnitParams = {};

  UuidCreate(&storageUnitParams.Guid);
  storageUnitParams.BlockCount  = sizeInBytes / BlockLength;
  storageUnitParams.BlockLength = BlockLength;
  lstrcpyA(reinterpret_cast<LPSTR>(storageUnitParams.ProductId),            productId.toStdString().c_str());
  lstrcpyA(reinterpret_cast<LPSTR>(storageUnitParams.ProductRevisionLevel), revision.toStdString().c_str());
  storageUnitParams.WriteProtected    = TRUE;
  //storageUnitParams.CacheSupported    = FALSE;
  //storageUnitParams.UnmapSupported    = FALSE;
  storageUnitParams.MaxTransferLength = 64 * 1024;

  try
  {
    _data.resize(sizeInBytes);
  }
  catch (const std::bad_alloc &ex)
  {
    throw MException::MCritical(WinSpd(), ERROR_NOT_ENOUGH_MEMORY, ex.what());
  }

  auto error = SpdStorageUnitCreate(nullptr, &storageUnitParams, &gStorageUnitInterface, &_storageUnit);
  if (error != ERROR_SUCCESS)
  {
    throw MException::MCritical(WinSpd(), error, "SpdStorageUnitCreate");
  }

  error = SpdStorageUnitStartDispatcher(_storageUnit, 0);
  if (error != ERROR_SUCCESS)
  {
    SpdStorageUnitDelete(_storageUnit);

    throw MException::MCritical(WinSpd(), error, "SpdStorageUnitStartDispatcher");
  }

  _storageUnit->UserContext = this;
}

void RamDiskWinSpd::stop()
{
  SpdStorageUnitShutdown(_storageUnit);
  SpdStorageUnitWaitDispatcher(_storageUnit);
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