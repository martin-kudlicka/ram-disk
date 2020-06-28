#include "pch.h"
#include "disks.h"

const QString Disks::Property::Group = "disks";

Disks::Disks()
{
  _settings.beginGroup(Property::Group);
}

quintptr Disks::count() const
{
  return _settings.childGroups().count();
}

const DiskSPtr &Disks::get(const MUuidPtr &id)
{
  Q_ASSERT_X(!id.isNull(), "Disks::get", "!id.isNull()");

  if (_disks.contains(id))
  {
    return _disks[id];
  }

  auto disk = _disks.insert(id, QSharedPointer<Disk>::create(id));

  return *disk;
}

MUuidPtr Disks::id(quintptr index) const
{
  return _settings.childGroups().at(index);
}

bool Disks::isEmpty() const
{
  return count() == 0;
}

void Disks::removeIndex(quintptr index)
{
  auto id2 = id(index);

  _disks.remove(id2);
  _settings.remove(id2.toString());
}