#include "pch.h"
#include "ramdiskoptions.h"

#include "ramdisks.h"

const QString RamDiskOptions::Property::Enabled = "enabled";
const QString RamDiskOptions::Property::Drive   = "drive";
const QString RamDiskOptions::Property::Size    = "size";
const QString RamDiskOptions::Property::Storage = "storage";

RamDiskOptions::RamDiskOptions(const MUuidPtr& id) : _id(id)
{
  beginGroup(RamDisks::Property::Group);
  beginGroup(id.toString());
}

QString RamDiskOptions::drive() const
{
  return value(Property::Drive).toString();
}

bool RamDiskOptions::enabled() const
{
  return value(Property::Enabled).toBool();
}

const MUuidPtr &RamDiskOptions::id() const
{
  return _id;
}

void RamDiskOptions::setEnabled(bool enabled)
{
  setValue(Property::Enabled, enabled);
}

quintptr RamDiskOptions::size() const
{
  return value(Property::Size).toUInt();
}

QString RamDiskOptions::storage() const
{
  return value(Property::Storage).toString();
}