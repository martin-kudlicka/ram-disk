#pragma once

#include "ui_mainwindow.h"
#include "ramdisksmodel.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
             MainWindow();
    virtual ~MainWindow() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    RamDisksModel       _ramDisksModel;
    Ui::MainWindowClass _ui;

    void editDisk    (const QModelIndex &index);
    void setupWidgets();

  private Q_SLOTS:
    void on_addRamDisk_clicked    (bool checked = false);
    void on_editRamDisk_clicked   (bool checked = false);
    void on_removeRamDisk_clicked (bool checked = false);
    void on_disks_doubleClicked   (const QModelIndex &index);
    void on_disks_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const;
};