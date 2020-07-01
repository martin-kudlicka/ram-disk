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
  _ui.disks->setModel(&_disksModel);

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

  _disksModel.insert(ramDiskDialog.options().id());

  // TODO
}

void MainWindow::on_actionRemoveRamDisk_triggered(bool checked /* false */)
{
  Q_UNUSED(checked);

  _disksModel.remove(_ui.disks->currentIndex());
}