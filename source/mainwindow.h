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
    RamDisksModel       _disksModel;
    Ui::MainWindowClass _ui;

    void setupWidgets();

  private Q_SLOTS:
    void on_actionAddRamDisk_triggered   (bool checked = false);
    void on_actionRemoveRamDisk_triggered(bool checked = false);
};