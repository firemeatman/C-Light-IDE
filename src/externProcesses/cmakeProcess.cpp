#include "cmakeProcess.h"

CmakeProcess::CmakeProcess(QObject *parent)
    : QObject{parent}
{
    process = new QProcess();
}

CmakeProcess::~CmakeProcess()
{
    process->deleteLater();
}

void CmakeProcess::setCmakeParam(Cmake_Param &params)
{

}

bool CmakeProcess::build()
{
    QProcess::ProcessState state = process->state();
    if(state != QProcess::NotRunning){
        return false;
    }
    QStringList args;
    args<<"-B"<<cmakeParam.buildDir<<"-G"<<cmakeParam.buildsystemName;
    args<<"-D"<<"CMAKE_C_COMPILER:STRING="+cmakeParam.cComplierPath;
    args<<"-D"<<"CMAKE_CXX_COMPILER:STRING="+cmakeParam.cxxComplierPath;
    args<<"-D"<<"CMAKE_MAKE_PROGRAM="+cmakeParam.buildsystemPath;
    args<<"-D"<<"CMAKE_INSTALL_PREFIX:PATH="+cmakeParam.installDir;
    QString argString;
    for(QString v : args){
        argString.append(v).append(" ");
    }
    emit msgRecved(argString);

    process->setWorkingDirectory(cmakeParam.cmakeFilePath);
    process->start(cmakeParam.cmakePath,args);
    process->waitForStarted();
    process->waitForFinished();
    if(process->exitStatus() == QProcess::NormalExit){
        return false;
    }

    return true;

}

bool CmakeProcess::install()
{
    QProcess::ProcessState state = process->state();
    if(state != QProcess::NotRunning){
        return false;
    }
    QStringList args;
    args<<"--build"<<cmakeParam.buildDir<<"--target"<<"all";
    QString argString;
    for(QString v : args){
        argString.append(v).append(" ");
    }
    emit msgRecved(argString);

    process->setWorkingDirectory(cmakeParam.cmakeFilePath);
    process->start(cmakeParam.cmakePath,args);
    process->waitForStarted();
    process->waitForFinished();
    if(process->exitStatus() == QProcess::NormalExit){
        return false;
    }

    return true;
}

QProcess *CmakeProcess::getProcess() const
{
    return process;
}

void CmakeProcess::setProcess(QProcess *newProcess)
{
    process = newProcess;
}

void CmakeProcess::_on_recvCmdOut()
{
    QByteArray data = process->readAllStandardOutput();
    QString utf8_str=QString::fromLocal8Bit(data);
    emit msgRecved(utf8_str);

}

void CmakeProcess::_on_recvCmdError()
{
    QByteArray data = process->readAllStandardOutput();
    QString utf8_str=QString::fromLocal8Bit(data);
    emit msgRecved(utf8_str);
}


