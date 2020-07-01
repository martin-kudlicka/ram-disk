#ifndef RAMDISKDIALOG_H
#define RAMDISKDIALOG_H

#include "ui_ramdiskdialog.h"
#include "ramdiskoptions.h"

class RamDiskDialog : public QDialog
{
  Q_OBJECT

  public:
             RamDiskDialog(QWidget *parent);
             RamDiskDialog(const MUuidPtr &id, QWidget *parent);
    virtual ~RamDiskDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    const RamDiskOptions &options() const;

  private:
    RamDiskOptions    _options;
    MWidgetSettings   _widgetSettings;
    Ui::RamDiskDialog _ui;

    void setupSettings();
    void setupWidgets ();

    virtual void accept() Q_DECL_OVERRIDE;
};

#endif