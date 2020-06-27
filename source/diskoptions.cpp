#include "pch.h"
#include "diskoptions.h"

const QString DiskOptions::Property::Size   = "size";
const QString DiskOptions::Property::Letter = "letter";

DiskOptions::DiskOptions(const MUuidPtr& id) : _id(id)
{
  beginGroup("disks");
  beginGroup(id.toString());
}