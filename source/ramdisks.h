#ifndef RAMDISKS_H
#define RAMDISKS_H

#include "ramdisk.h"

class RamDisksModel;

class RamDisks
{
  public:
    struct Property
    {
      static const QString Group;
    };

    RamDisks(RamDisksModel *ramDisksModel);

          quintptr     count      ()                   const;
    const RamDiskSPtr &get        (const MUuidPtr &id);
          MUuidPtr     id         (quintptr index)     const;
          quintptr     index      (const MUuidPtr &id) const;
          bool         isEmpty    ()                   const;
          void         removeIndex(quintptr index);

  private:
    QHash<MUuidPtr, RamDiskSPtr> _disks;
    QSettings                    _settings;
    RamDisksModel               *_ramDisksModel;

    RamDiskSPtrList get();
};

#endif