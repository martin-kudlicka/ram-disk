#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include "ui_optionsdialog.h"

class OptionsDialog : public QDialog
{
  public:
    OptionsDialog(QWidget *parent);

  private:
    Ui::OptionsDialog _ui;
    MWidgetSettings   _widgetSettings;

    void setupSettings();

    virtual void accept() Q_DECL_OVERRIDE;
};

#endif