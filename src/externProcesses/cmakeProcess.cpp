#include "cmakeProcess.h"

#include <QFileInfo>
#include <QDir>
CmakeProcess::CmakeProcess(QObject *parent)
    : QObject{parent}
{
    process = new QProcess();
    connect(process, &QProcess::readyReadStandardOutput, this, &CmakeProcess::_on_recvCmdOut);
    connect(process, &QProcess::readyReadStandardError, this, &CmakeProcess::_on_recvCmdError);
}

CmakeProcess::~CmakeProcess()
{
    process->deleteLater();
}

void CmakeProcess::setCmakeParam(Cmake_Param &params)
{
    this->cmakeParam.buildDir = params.buildDir;
    this->cmakeParam.buildsystemName = params.buildsystemName;
    this->cmakeParam.buildsystemPath = params.buildsystemPath;
    this->cmakeParam.cComplierPath = params.cComplierPath;
    this->cmakeParam.cxxComplierPath = params.cxxComplierPath;
    this->cmakeParam.cmakeFilePath = params.cmakeFilePath;
    this->cmakeParam.cmakePath = params.cmakePath;
    this->cmakeParam.installDir = params.installDir;

}

bool CmakeProcess::build()
{
    QProcess::ProcessState state = process->state();
    if(state != QProcess::NotRunning){
        return false;
    }
    QStringList args;

    args<<"-B"<<cmakeParam.buildDir;
    if(!cmakeParam.buildsystemName.isEmpty()){
        args<<"-G"<<cmakeParam.buildsystemName;
    }
    if(!cmakeParam.cComplierPath.isEmpty()){
        args<<"-D"<<"CMAKE_C_COMPILER:STRING="+cmakeParam.cComplierPath;
    }
    if(!cmakeParam.cxxComplierPath.isEmpty()){
        args<<"-D"<<"CMAKE_CXX_COMPILER:STRING="+cmakeParam.cxxComplierPath;
    }
    if(!cmakeParam.cxxComplierPath.isEmpty()){
        args<<"-D"<<"CMAKE_MAKE_PROGRAM="+cmakeParam.buildsystemPath;
    }
    args<<"-D"<<"CMAKE_INSTALL_PREFIX:PATH="+cmakeParam.installDir;
    args<<"-D"<<"CMAK_BUILD_TYPE:STRING="+QStringLiteral("Debug");
    args<<"-D"<<"CMAKE_EXPORT_COMPILE_COMMANDS="+QString::number(1);
    QString argString;
    for(QString v : args){
        argString.append(v).append(" ");
    }
    emit msgRecved(argString);

    QFileInfo fileInfo(cmakeParam.cmakeFilePath);
    process->setWorkingDirectory(fileInfo.dir().path());
    process->start(cmakeParam.cmakePath,args);
    process->waitForStarted();
    process->waitForFinished();
    if(process->exitStatus() == QProcess::NormalExit){
        return true;

    }else{
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

    QFileInfo fileInfo(cmakeParam.cmakeFilePath);
    process->setWorkingDirectory(fileInfo.dir().path());
    process->start(cmakeParam.cmakePath,args);
    process->waitForStarted();
    process->waitForFinished();
    if(process->exitStatus() == QProcess::NormalExit){
        return true;

    }else{
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


