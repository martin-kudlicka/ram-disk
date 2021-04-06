#include "pch.h"
#include "optionsdialog.h"

#include "options.h"

OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent), _widgetSettings(gOptions.data())
{
  _ui.setupUi(this);

  setupSettings();
}

void OptionsDialog::setupSettings()
{
  _widgetSettings.setWidget(Options::Property::MinimizeToTray, _ui.minimizeToTray);
  _widgetSettings.setWidget(Options::Property::StartMinimized, _ui.startMinimized);

  _widgetSettings.load();
}

void OptionsDialog::accept()
{
  _widgetSettings.save();

  QDialog::accept();
}