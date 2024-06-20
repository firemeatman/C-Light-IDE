
#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H


#include <QString>
#include <QSettings>
#include <QList>

#include "../GUI/window/mainWindow/mainwindow.h"
#include "../project/projectManager.h"
#include "../file/editCodeManager.h"
#include "../externProcesses/externProcessThread.h"
#include "../model/modelDataDef.h"

#define SAFE_DELE_P(p) do{\
if(p){\
delete p;\
p = nullptr;\
}\
}while(0);

typedef struct{
    QString createProjectPath;
    QString openProjectPath;
}LastChoices;


class GlobalData{
public:

    GlobalData();

    static MainWindow* mainWindow;
    static ProjectManager* projectManager;
    static EditCodeManager* editCodeManager;
    static ExternProcessThread* ExternProcessThread;

    static LastChoices lastChoices;
    static QList<HistoryProject> historyProjectList;

    // static QString complierDir;
    // static QString makeExePath;
    // static QString mainMakefilePath;
    // static QString mainMakefileDir;
    // static QString mainMakefileFullName;
    // static QString targetExeDir;
    // static QString targetExeName;
    // static QString debugerExePath;
    // static QString lastProjectDir;


};



#endif // GLOBAL_DATA_H
