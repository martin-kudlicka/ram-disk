#include "pch.h"
#include "ramdiskdialog.h"

#include "storages.h"

RamDiskDialog::RamDiskDialog(QWidget *parent) : RamDiskDialog(MUuidPtr::createUuid(), parent)
{
}

RamDiskDialog::RamDiskDialog(const MUuidPtr &id, QWidget *parent) : QDialog(parent), _options(id), _widgetSettings(&_options)
{
  _ui.setupUi(this);

  setupWidgets();
  setupSettings();
}

const RamDiskOptions &RamDiskDialog::options() const
{
  return _options;
}

void RamDiskDialog::setupSettings()
{
  _widgetSettings.setWidget(RamDiskOptions::Property::Enabled, _ui.enabled);
  _widgetSettings.setWidget(RamDiskOptions::Property::Drive,   _ui.drive);
  _widgetSettings.setWidget(RamDiskOptions::Property::Size,    _ui.size);
  _widgetSettings.setWidget(RamDiskOptions::Property::Storage, _ui.storage);

  _widgetSettings.load();
}

void RamDiskDialog::setupWidgets()
{
  for (auto letter = 'A'; letter <= 'Z'; ++letter)
  {
    auto drive = QString(letter) + ':';
    _ui.drive->addItem(drive, drive);
  }

  for (const auto &storage : gStorages->toRawList())
  {
    _ui.storage->addItem(storage->name(), storage->name());
  }
}

void RamDiskDialog::accept()
{
  _widgetSettings.save();

  QDialog::accept();
}