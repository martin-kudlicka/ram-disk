#include "pch.h"
#include "diskdialog.h"

#include "storages.h"

DiskDialog::DiskDialog(QWidget *parent) : DiskDialog(MUuidPtr::createUuid(), parent)
{
}

DiskDialog::DiskDialog(const MUuidPtr &id, QWidget *parent) : QDialog(parent), _options(id), _widgetSettings(&_options)
{
  _ui.setupUi(this);

  setupWidgets();
  setupSettings();
}

void DiskDialog::setupSettings()
{
  _widgetSettings.setWidget(DiskOptions::Property::Enabled, _ui.enabled);
  _widgetSettings.setWidget(DiskOptions::Property::Drive,   _ui.drive);
  _widgetSettings.setWidget(DiskOptions::Property::Size,    _ui.size);
  _widgetSettings.setWidget(DiskOptions::Property::Storage, _ui.storage);

  _widgetSettings.load();
}

void DiskDialog::setupWidgets()
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

void DiskDialog::accept()
{
  _widgetSettings.save();

  QDialog::accept();
}