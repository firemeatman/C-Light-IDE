
#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H


#include <QString>
#include <QMutex>
#include "../GUI/mainwindow.h"
#include "../codeFileSys/codeFileSys.h"
#include "../externProcesses/externProcessThread.h"
//class MainWindow;
//class TerminalWidget;
//class TerminalSysteam;

class GlobalData{
public:

    GlobalData();

    static MainWindow* global_mainWindow;
    static CodeFileSys* codeFileSys;
    static ExternProcessThread* ExternProcessThread;

    static QString complierDir;
    static QString makeExePath;
    static QString mainMakefilePath;
    static QString mainMakefileDir;
    static QString mainMakefileFullName;
    static QString targetExeDir;
    static QString targetExeName;
    static QString debugerExePath;

    static QString lastProjectDir;


private:
//    static QMutex makeMutex;
//    static QMutex debugMutex;


};



#endif // GLOBAL_DATA_H
