#include "global_data.h"


MainWindow* GlobalData::global_mainWindow = nullptr;

CodeFileSys* GlobalData::codeFileSys = nullptr;
ExternProcessThread* GlobalData::ExternProcessThread = nullptr;


QMutex GlobalData::makeMutex;
QMutex GlobalData::debugMutex;
QString GlobalData::ComplierPath = "";
QString GlobalData::MakeProgramPath = "";
QString GlobalData::DebugerPath = "";
QString GlobalData::MakeFilePath = "";

GlobalData::GlobalData()
{

}

QString GlobalData::getDebugerPath()
{
    debugMutex.lock();
    QString str = DebugerPath;
    debugMutex.unlock();
    return str;
}

void GlobalData::setDebugerPath(const QString &newDebugerPath)
{
    debugMutex.lock();
    DebugerPath = newDebugerPath;
    debugMutex.unlock();
}

QString GlobalData::getMakeProgramPath()
{
    makeMutex.lock();
    QString str = MakeProgramPath;
    makeMutex.unlock();
    return str;

}

void GlobalData::setMakeProgramPath(const QString &newMakeProgramPath)
{
    makeMutex.lock();
    MakeProgramPath = newMakeProgramPath;
    makeMutex.unlock();
}

QString GlobalData::getMakeFilePath()
{
    makeMutex.lock();
    QString str = MakeFilePath;
    makeMutex.unlock();
    return str;

}

void GlobalData::setMakeFilePath(const QString &newMakeFilePath)
{
    makeMutex.lock();
    MakeFilePath = newMakeFilePath;
    makeMutex.unlock();
}
