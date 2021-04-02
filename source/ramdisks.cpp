#include "pch.h"
#include "ramdisks.h"

const QString RamDisks::Property::Group = "disks";

RamDisks::RamDisks()
{
  _settings.beginGroup(Property::Group);

  for (const auto &disk : get())
  {
    if (disk->options().enabled())
    {
      disk->start();
    }
  }
}

quintptr RamDisks::count() const
{
  return _settings.childGroups().count();
}

const RamDiskSPtr &RamDisks::get(const MUuidPtr &id)
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

quintptr RamDisks::index(const MUuidPtr &id) const
{
  quintptr index2 = 0;

  for (const auto &id2 : _settings.childGroups())
  {
    if (id2 == id.toString())
    {
      return index2;
    }

    ++index2;
  }

  Q_UNREACHABLE();
  return std::numeric_limits<quintptr>::max();
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

RamDiskSPtrList RamDisks::get()
{
  {
    // initialize disks if needed
    auto diskCount = count();
    if (gsl::narrow<decltype(diskCount)>(_disks.count()) != diskCount)
    {
      for (decltype(diskCount) index2 = 0; index2 < diskCount; ++index2)
      {
        get(id(index2));
      }
    }
  }

  return _disks.values();
}