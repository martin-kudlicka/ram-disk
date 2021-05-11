#include "pch.h"
#include "mainwindow.h"

#include "ramdiskdialog.h"
#include "optionsdialog.h"
#include "options.h"

MainWindow::MainWindow() : QMainWindow()
{
    _ui.setupUi(this);

    setupWidgets();
}

void MainWindow::show()
{
  if (gOptions->startMinimized())
  {
    setWindowState(Qt::WindowMinimized);
  }
  else
  {
    QMainWindow::show();
  }
}

void MainWindow::editDisk(const QModelIndex &index)
{
  auto id = _ramDisksModel.id(index);

  RamDiskDialog(id, this).exec();
}

void MainWindow::setupWidgets()
{
  _ui.disks->setModel(&_ramDisksModel);

  _ui.disks->header()->setSectionResizeMode(gsl::narrow<int>(RamDisksModel::Column::Enabled), QHeaderView::ResizeToContents);

  _trayIcon.setIcon(windowIcon());
  _trayIcon.setToolTip(windowTitle());

  connect(_ui.disks->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::on_disks_selectionChanged);
  connect(&_trayIcon,                  &QSystemTrayIcon::activated,            this, &MainWindow::on_trayIcon_activated);
}

bool MainWindow::event(QEvent *event)
{
  switch (event->type())
  {
    case QEvent::WindowStateChange:
      if (isMinimized() && gOptions->minimizeToTray())
      {
        hide();
        _trayIcon.show();
      }
  }

  return QMainWindow::event(event);
}

void MainWindow::on_actionOptions_triggered(bool checked /* false */)
{
  Q_UNUSED(checked);

  OptionsDialog(this).exec();
}

void MainWindow::on_addRamDisk_clicked(bool checked /* false */)
{
  Q_UNUSED(checked);

  RamDiskDialog ramDiskDialog(this);
  if (ramDiskDialog.exec() == QDialog::Rejected)
  {
    return;
  }

  _ramDisksModel.insert(ramDiskDialog.options().id());

  auto ramDisk = _ramDisksModel.ramDisk(ramDiskDialog.options().id());
  if (ramDisk->options().enabled())
  {
    try
    {
      ramDisk->start();
    }
    catch (const MException::Critical &ex)
    {
      mCriticalEx(ex);

      ramDisk->options().setEnabled(false);
      _ramDisksModel.setDataChanged(ramDisk->options().id(), RamDisksModel::Column::Enabled);
    }
  }
}

void MainWindow::on_editRamDisk_clicked(bool checked /* false */)
{
  Q_UNUSED(checked);

  editDisk(_ui.disks->currentIndex());
}

void MainWindow::on_removeRamDisk_clicked(bool checked /* false */)
{
  Q_UNUSED(checked);

  auto ramDisk = _ramDisksModel.ramDisk(_ui.disks->currentIndex());
  if (ramDisk->running())
  {
    try
    {
      ramDisk->stop();
    }
    catch (const MException::Critical &ex)
    {
      mCriticalEx(ex);
    }
  }

  _ramDisksModel.remove(_ui.disks->currentIndex());
}

void MainWindow::on_disks_doubleClicked(const QModelIndex &index)
{
  editDisk(index);
}

void MainWindow::on_disks_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const
{
  Q_UNUSED(selected);
  Q_UNUSED(deselected);

  auto isSelected = !_ui.disks->selectionModel()->selectedRows().isEmpty();

  _ui.editRamDisk->setEnabled(isSelected);
  _ui.removeRamDisk->setEnabled(isSelected);
}

void MainWindow::on_trayIcon_activated(QSystemTrayIcon::ActivationReason reason)
{
  if (reason == QSystemTrayIcon::DoubleClick)
  {
    _trayIcon.hide();
    showNormal();
    activateWindow();
  }
}