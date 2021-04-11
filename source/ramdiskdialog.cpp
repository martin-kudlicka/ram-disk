#include "pch.h"
#include "ramdiskdialog.h"

#include "storages.h"

RamDiskDialog::RamDiskDialog(QWidget *parent) : MOptionsDialog(parent)
{
}

RamDiskDialog::RamDiskDialog(const MUuidPtr &id, QWidget *parent) : MOptionsDialog(id, parent)
{
  _ui.changesNotice->setVisible(_ui.enabled->isChecked());
}

void RamDiskDialog::setupSettings()
{
  _widgetSettings.setWidget(RamDiskOptions::Property::Enabled, _ui.enabled);
  _widgetSettings.setWidget(RamDiskOptions::Property::Drive,   _ui.drive);
  _widgetSettings.setWidget(RamDiskOptions::Property::Size,    _ui.size);
  _widgetSettings.setWidget(RamDiskOptions::Property::Storage, _ui.storage);

  _widgetSettings.load();
}

void RamDiskDialog::setupWidgets() const
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