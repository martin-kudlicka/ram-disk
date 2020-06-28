#include "pch.h"
#include "ramdisks.h"

const QString RamDisks::Property::Group = "disks";

RamDisks::RamDisks()
{
  _settings.beginGroup(Property::Group);
}

quintptr RamDisks::count() const
{
  return _settings.childGroups().count();
}

const DiskSPtr &RamDisks::get(const MUuidPtr &id)
{
  Q_ASSERT_X(!id.isNull(), "Disks::get", "!id.isNull()");

  if (_disks.contains(id))
  {
    return _disks[id];
  }

  auto disk = _disks.insert(id, QSharedPointer<RamDisk>::create(id));

  return *disk;
}

MUuidPtr RamDisks::id(quintptr index) const
{
  return _settings.childGroups().at(index);
}

bool RamDisks::isEmpty() const
{
  return count() == 0;
}

void RamDisks::removeIndex(quintptr index)
{
  auto id2 = id(index);

  _disks.remove(id2);
  _settings.remove(id2.toString());
}