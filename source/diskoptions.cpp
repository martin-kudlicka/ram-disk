#include "pch.h"
#include "diskoptions.h"

#include "disks.h"

const QString DiskOptions::Property::Enabled = "enabled";
const QString DiskOptions::Property::Drive   = "drive";
const QString DiskOptions::Property::Size    = "size";
const QString DiskOptions::Property::Storage = "storage";

DiskOptions::DiskOptions(const MUuidPtr& id) : _id(id)
{
  beginGroup(Disks::Property::Group);
  beginGroup(id.toString());
}

QString DiskOptions::drive() const
{
  return value(Property::Drive).toString();
}

bool DiskOptions::enabled() const
{
  return value(Property::Enabled).toBool();
}

quintptr DiskOptions::size() const
{
  return value(Property::Size).toUInt();
}