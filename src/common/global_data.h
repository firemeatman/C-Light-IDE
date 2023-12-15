
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
    static QString ComplierPath;

private:

    static QString MakeProgramPath;
    static QString DebugerPath;
    static QString MakeFilePath;

    static QMutex makeMutex;
    static QMutex debugMutex;

public:

    static QString getMakeFilePath();
    static void setMakeFilePath(const QString &newMakeFilePath);

    static QString getMakeProgramPath();
    static void setMakeProgramPath(const QString &newMakeProgramPath);


    static QString getDebugerPath();
    static void setDebugerPath(const QString &newDebugerPath);
};



#endif // GLOBAL_DATA_H
