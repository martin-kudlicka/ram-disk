#ifndef RAMDISKDIALOG_H
#define RAMDISKDIALOG_H

#include "ui_ramdiskdialog.h"
#include "ramdiskoptions.h"

class RamDiskDialog : public MOptionsDialog<Ui::RamDiskDialog, RamDiskOptions>
{
  Q_OBJECT

  public:
             RamDiskDialog(QWidget *parent);
             RamDiskDialog(const MUuidPtr &id, QWidget *parent);
    virtual ~RamDiskDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    virtual void setupSettings()       Q_DECL_OVERRIDE;
    virtual void setupWidgets () const Q_DECL_OVERRIDE;
};

#endif