
#include "./GUI/mainwindow.h"

#include <QApplication>
#include "common/global_data.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    global_mainWindow = &w;
    w.show();
    return a.exec();
}
