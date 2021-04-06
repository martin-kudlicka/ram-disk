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
    QSystemTrayIcon     _trayIcon;

    void editDisk    (const QModelIndex &index);
    void setupWidgets();

    virtual bool event(QEvent *event) Q_DECL_OVERRIDE;

  private Q_SLOTS:
    void on_actionOptions_triggered(bool checked = false);
    void on_addRamDisk_clicked     (bool checked = false);
    void on_editRamDisk_clicked    (bool checked = false);
    void on_removeRamDisk_clicked  (bool checked = false);
    void on_disks_doubleClicked    (const QModelIndex &index);
    void on_disks_selectionChanged (const QItemSelection &selected, const QItemSelection &deselected) const;
    void on_trayIcon_activated     (QSystemTrayIcon::ActivationReason reason);
};