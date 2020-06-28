#include "pch.h"
#include "mainwindow.h"

#include "diskdialog.h"

MainWindow::MainWindow() : QMainWindow()
{
    _ui.setupUi(this);

    setupWidgets();
}

void MainWindow::setupWidgets()
{
  _ui.disks->setModel(&_disksModel);

  _ui.disks->header()->setSectionResizeMode(static_cast<int>(DisksModel::Column::Enabled), QHeaderView::ResizeToContents);
}

void MainWindow::on_actionAddRamDisk_triggered(bool checked /* false */)
{
  Q_UNUSED(checked);

  DiskDialog diskDialog(this);
  if (diskDialog.exec() == QDialog::Rejected)
  {
    return;
  }

  // TODO
}

void MainWindow::on_actionRemoveRamDisk_triggered(bool checked /* false */)
{
  Q_UNUSED(checked);

  _disksModel.remove(_ui.disks->currentIndex());
}