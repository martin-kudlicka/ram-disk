#ifndef RAMDISKWINSPD_H
#define RAMDISKWINSPD_H

#include "../../common/ramdiskinterface.h"

class RamDiskWinSpd : public RamDiskInterface
{
  public:
             RamDiskWinSpd(const RamDiskParameters &parameters);
    virtual ~RamDiskWinSpd() Q_DECL_EQ_DEFAULT;

    bool read(LPBYTE source, quintptr blockAddress, quintptr blockCount, SPD_STORAGE_UNIT_STATUS *status) const;
    bool unmap(const SPD_UNMAP_DESCRIPTOR *descriptors, quintptr count);
    bool write(LPCBYTE destination, quintptr blockAddress, quintptr blockCount, SPD_STORAGE_UNIT_STATUS *status);

  private:
    QVector<BYTE>     _data;
    SPD_STORAGE_UNIT *_storageUnit;

    bool copyBuffer(LPCBYTE source, LPBYTE destination, quintptr size, quint8 senseCode, SPD_STORAGE_UNIT_STATUS *status) const;

    virtual bool start() Q_DECL_OVERRIDE;
    virtual void stop () Q_DECL_OVERRIDE;

    static BOOLEAN exceptionFilter(DWORD code, PEXCEPTION_POINTERS pointers, quintptr *dataAddress);
};

#endif