#include "pch.h"
#include "mainwindow.h"

#include "ramdiskdialog.h"

MainWindow::MainWindow() : QMainWindow()
{
    _ui.setupUi(this);

    setupWidgets();
}

void MainWindow::setupWidgets()
{
  _ui.disks->setModel(&_ramDisksModel);

  _ui.disks->header()->setSectionResizeMode(static_cast<int>(RamDisksModel::Column::Enabled), QHeaderView::ResizeToContents);
}

void MainWindow::on_actionAddRamDisk_triggered(bool checked /* false */)
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
    ramDisk->start();
  }
}

void MainWindow::on_actionRemoveRamDisk_triggered(bool checked /* false */)
{
  Q_UNUSED(checked);

  _ramDisksModel.remove(_ui.disks->currentIndex());
}