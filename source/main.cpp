#include "pch.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
  MApplication application(argc, argv);

  MainWindow mainWindow;
  mainWindow.show();

  return application.exec();
}