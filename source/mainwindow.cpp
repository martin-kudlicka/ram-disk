#include "pch.h"
#include "mainwindow.h"

#include "ramdiskdialog.h"

MainWindow::MainWindow() : QMainWindow()
{
    _ui.setupUi(this);

    setupWidgets();
}

void MainWindow::editDisk(const QModelIndex &index)
{
  auto id = _ramDisksModel.id(index);

  RamDiskDialog(id, this).exec();
}

void MainWindow::setupWidgets()
{
  _ui.disks->setModel(&_ramDisksModel);

  _ui.disks->header()->setSectionResizeMode(static_cast<int>(RamDisksModel::Column::Enabled), QHeaderView::ResizeToContents);

  connect(_ui.disks->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::on_disks_selectionChanged);
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
    ramDisk->start();
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
    ramDisk->stop();
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