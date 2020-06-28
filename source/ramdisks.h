#ifndef RAMDISKS_H
#define RAMDISKS_H

#include "ramdisk.h"

class RamDisks
{
  public:
    struct Property
    {
      static const QString Group;
    };

    RamDisks();

          quintptr  count      ()               const;
    const DiskSPtr &get        (const MUuidPtr &id);
          MUuidPtr  id         (quintptr index) const;
          bool      isEmpty    ()               const;
          void      removeIndex(quintptr index);

  private:
    QHash<MUuidPtr, DiskSPtr> _disks;
    QSettings                 _settings;
};

#endif