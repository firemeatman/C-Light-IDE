
#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H


#include <QString>
#include <QMutex>
#include "../GUI/mainwindow.h"
#include "../system/codeFileSys.h"
#include "../externProcesses/externProcessThread.h"
#include "projectConfig.h"
class GlobalData{
public:

    GlobalData();

    static MainWindow* global_mainWindow;
    static CodeFileSys* codeFileSys;
    static ExternProcessThread* ExternProcessThread;
    static ProjectConfig* projectConfig;

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
