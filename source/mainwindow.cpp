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