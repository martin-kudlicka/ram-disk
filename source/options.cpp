#include "pch.h"
#include "options.h"

MLazySingleton<Options> gOptions;

Options::Options()
{
  beginGroup("options");
}

bool Options::minimizeToTray() const
{
  return value(Property::MinimizeToTray).toBool();
}