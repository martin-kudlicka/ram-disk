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