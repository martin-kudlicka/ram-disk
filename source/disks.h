#ifndef DISKS_H
#define DISKS_H

#include "disk.h"

class Disks
{
  public:
    struct Property
    {
      static const QString Group;
    };

    Disks();

          quintptr  count  ()               const;
    const DiskSPtr &get    (const MUuidPtr &id);
          MUuidPtr  id     (quintptr index) const;
          bool      isEmpty()               const;

  private:
    QHash<MUuidPtr, DiskSPtr> _disks;
    QSettings                 _settings;
};

#endif