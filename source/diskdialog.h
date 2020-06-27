#ifndef DISKDIALOG_H
#define DISKDIALOG_H

#include "ui_diskdialog.h"
#include "diskoptions.h"

class DiskDialog : public QDialog
{
  Q_OBJECT

  public:
             DiskDialog(QWidget *parent);
             DiskDialog(const MUuidPtr &id, QWidget *parent);
    virtual ~DiskDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    DiskOptions      _options;
    MWidgetSettings  _widgetSettings;
    Ui::DiskDialog   _ui;

    void setupSettings();
    void setupWidgets ();

    virtual void accept() Q_DECL_OVERRIDE;
};

#endif