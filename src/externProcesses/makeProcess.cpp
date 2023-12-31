
#include "makeProcess.h"
#include <QDebug>
MakeProcess::MakeProcess(QObject *parent)
    : QObject{parent}
{
   process = new QProcess();
   connect(process, &QProcess::readyReadStandardOutput, this, &MakeProcess::_on_recvCmdOut);
   connect(process, &QProcess::readyReadStandardError, this, &MakeProcess::_on_recvCmdError);
}

MakeProcess::~MakeProcess()
{
   process->deleteLater();
}



void MakeProcess::startProcess(QString &exePath, QString& workDir)
{
   process->setWorkingDirectory(workDir);
   process->start(exePath);
   process->waitForStarted();
}

void MakeProcess::closeProcess()
{
   process->close();
   process->waitForFinished();
}

bool MakeProcess::make(QString &makeExePath, QString &mkFileDir, QString &mkFileName)
{
   QProcess::ProcessState state = process->state();
   if(state != QProcess::NotRunning){
       return false;
   }
   QStringList args;
   args<<"-C"<<mkFileDir<<"-f"<<mkFileName;
   //process->setNativeArguments();  windows平台下用这个。
   process->start(makeExePath,args);
   process->waitForStarted();
   process->waitForFinished();
   if(process->exitStatus() == QProcess::NormalExit){
       int exitCode = process->exitCode();
       qDebug()<<"make退出代码: "<<exitCode;

   }else{
       qDebug()<<"make崩溃了";
   }

   return true;

}

bool MakeProcess::clean(QString &makeExePath, QString &mkFileDir, QString &mkFileName)
{
   QProcess::ProcessState state = process->state();
   if(state != QProcess::NotRunning){
       return false;
   }
   QStringList args;
   args<<"-C"<<mkFileDir<<"-f"<<mkFileName<<"clean";

   //process->setNativeArguments();  windows平台下用这个。
   process->start(makeExePath,args);
   process->waitForStarted();
   process->waitForFinished();
   if(process->exitStatus() == QProcess::NormalExit){
       int exitCode = process->exitCode();
       qDebug()<<"make退出代码: "<<exitCode;

   }else{
       qDebug()<<"make崩溃了";
   }

   return true;
}

QProcess *MakeProcess::getProcess() const
{
   return process;
}

void MakeProcess::_on_recvCmdOut()
{
   QByteArray data = process->readAllStandardOutput();
   QString utf8_str=QString::fromLocal8Bit(data);
   emit msgRecved(utf8_str);

}

void MakeProcess::_on_recvCmdError()
{
   QByteArray data = process->readAllStandardOutput();
   QString utf8_str=QString::fromLocal8Bit(data);
   emit msgRecved(utf8_str);
}

