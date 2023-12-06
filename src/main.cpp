
#include "./GUI/mainwindow.h"

#include <QApplication>
#include "common/global_data.h"
#include "terminalSys/terminalSysteam.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    GlobalData::global_mainWindow = &w;
    GlobalData::global_terminalSysteam = new TerminalSysteam();
    GlobalData::global_terminalSysteam->startTerminal();
    w.show();
    int flag = a.exec();

    if(GlobalData::global_terminalSysteam != nullptr){
        delete GlobalData::global_terminalSysteam;
        GlobalData::global_terminalSysteam = nullptr;
    }

    return flag;
}
