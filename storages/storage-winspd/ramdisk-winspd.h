#ifndef RAMDISKWINSPD_H
#define RAMDISKWINSPD_H

#include "../../common/ramdiskinterface.h"

class RamDiskWinSpd : public RamDiskInterface
{
  public:
             RamDiskWinSpd(const RamDiskParameters &parameters);
    virtual ~RamDiskWinSpd() Q_DECL_EQ_DEFAULT;

  private:
    QVector<BYTE>     _data;
    SPD_STORAGE_UNIT *_storageUnit;

    virtual bool start() Q_DECL_OVERRIDE;
    virtual void stop () Q_DECL_OVERRIDE;
};

#endif