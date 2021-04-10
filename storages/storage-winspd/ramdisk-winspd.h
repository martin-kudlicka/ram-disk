#ifndef RAMDISKWINSPD_H
#define RAMDISKWINSPD_H

#include "../../common/ramdiskinterface.h"

class RamDiskWinSpd : public RamDiskInterface
{
  public:
             RamDiskWinSpd(const RamDiskParameters &parameters);
    virtual ~RamDiskWinSpd() Q_DECL_EQ_DEFAULT;

  private:
    QScopedPointer<MWinSpdBufferDevice> _bufferDevice;
    MString                             _mountPoint;

    virtual void start() Q_DECL_OVERRIDE;
    virtual void stop () Q_DECL_OVERRIDE;
};

#endif