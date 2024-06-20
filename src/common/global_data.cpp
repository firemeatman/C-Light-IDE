#include "global_data.h"


MainWindow* GlobalData::mainWindow = nullptr;
ProjectManager* GlobalData::projectManager = nullptr;
EditCodeManager* GlobalData::editCodeManager = nullptr;
ExternProcessThread* GlobalData::ExternProcessThread = nullptr;
LastChoices GlobalData::lastChoices;
QList<HistoryProject> GlobalData::historyProjectList;

// QString GlobalData::complierDir;
// QString GlobalData::makeExePath;
// QString GlobalData::mainMakefilePath;
// QString GlobalData::mainMakefileDir;
// QString GlobalData::mainMakefileFullName;
// QString GlobalData::targetExeDir;
// QString GlobalData::targetExeName;
// QString GlobalData::debugerExePath;

// QString GlobalData::lastProjectDir;

GlobalData::GlobalData()
{

}

