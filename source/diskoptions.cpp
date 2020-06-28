#include "pch.h"
#include "diskoptions.h"

#include "disks.h"

const QString DiskOptions::Property::Enabled = "enabled";
const QString DiskOptions::Property::Letter  = "letter";
const QString DiskOptions::Property::Size    = "size";

DiskOptions::DiskOptions(const MUuidPtr& id) : _id(id)
{
  beginGroup(Disks::Property::Group);
  beginGroup(id.toString());
}

bool DiskOptions::enabled() const
{
  return value(Property::Enabled).toBool();
}

QChar DiskOptions::letter() const
{
  return value(Property::Letter).toChar();
}

quintptr DiskOptions::size() const
{
  return value(Property::Size).toUInt();
}