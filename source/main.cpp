#include "pch.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
  MApplication application(argc, argv);

  mAnalytics->setId("57ff7de874d5b98ab63f48906b45d6c4b23d0b50");

  MainWindow mainWindow;
  mainWindow.show();

  return application.exec();
}