#include "global_data.h"


MainWindow* GlobalData::global_mainWindow = nullptr;

CodeFileSys* GlobalData::codeFileSys = nullptr;
ExternProcessThread* GlobalData::ExternProcessThread = nullptr;

QString GlobalData::complierDir;
QString GlobalData::makeExePath;
QString GlobalData::mainMakefilePath;
QString GlobalData::mainMakefileDir;
QString GlobalData::mainMakefileFullName;
QString GlobalData::targetExeDir;
QString GlobalData::targetExeName;
QString GlobalData::debugerExePath;

QString GlobalData::lastProjectDir;

GlobalData::GlobalData()
{

}

