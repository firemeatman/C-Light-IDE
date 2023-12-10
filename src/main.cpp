
#include "./GUI/mainwindow.h"

#include <QApplication>
#include "common/global_data.h"
#include "terminalSys/terminalSysteam.h"
#include "codeFileSys/codeFileSys.h"

void init_app();
void relase_resouse();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    GlobalData::global_mainWindow = &w;
    init_app();

    w.show();
    int flag = a.exec();
    relase_resouse();
    return flag;
}

void init_app(){
    GlobalData::global_terminalSysteam = new TerminalSysteam();
    GlobalData::global_terminalSysteam->startTerminal();
    GlobalData::codeFileSys = new CodeFileSys();
}

void relase_resouse(){
    if(GlobalData::global_terminalSysteam != nullptr){
        delete GlobalData::global_terminalSysteam;
        GlobalData::global_terminalSysteam = nullptr;
    }
    if(GlobalData::codeFileSys != nullptr){
        delete GlobalData::codeFileSys;
        GlobalData::codeFileSys = nullptr;
    }
}

