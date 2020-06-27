#include "pch.h"
#include "diskdialog.h"

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
  _widgetSettings.setWidget(DiskOptions::Property::Size,   _ui.size);
  _widgetSettings.setWidget(DiskOptions::Property::Letter, _ui.letter);

  _widgetSettings.load();
}

void DiskDialog::setupWidgets()
{
  for (auto letter = 'A'; letter <= 'Z'; ++letter)
  {
    _ui.letter->addItem(QString(letter));
  }
}

void DiskDialog::accept()
{
  _widgetSettings.save();

  QDialog::accept();
}