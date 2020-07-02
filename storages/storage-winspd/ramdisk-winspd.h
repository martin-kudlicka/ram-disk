#ifndef RAMDISKWINSPD_H
#define RAMDISKWINSPD_H

#include "../../common/ramdiskinterface.h"

class RamDiskWinSpd : public RamDiskInterface
{
  public:
             RamDiskWinSpd(const RamDiskParameters &parameters);
    virtual ~RamDiskWinSpd() Q_DECL_EQ_DEFAULT;

  private:
    virtual bool start() const Q_DECL_OVERRIDE;
    virtual bool stop () const Q_DECL_OVERRIDE;
};

#endif