
#include "terminalSysteam.h"

#include "../common/global_data.h"
TerminalSysteam::TerminalSysteam(QObject *parent) : QObject(parent)
{
    //terminalThread = new TerminalThread();
    cmdProcess = new QProcess(this);

    connect(cmdProcess, &QProcess::readyReadStandardOutput, this, &TerminalSysteam::_on_recvCmdOut);
    connect(cmdProcess, &QProcess::readyReadStandardError, this, &TerminalSysteam::_on_recvCmdError);


}

TerminalSysteam::~TerminalSysteam()
{
    if(cmdProcess != nullptr){
        cmdProcess->close();
        cmdProcess->waitForFinished();
        cmdProcess->deleteLater();
    }
}

void TerminalSysteam::startTerminal()
{
//    if(terminalThread == nullptr){
//        terminalThread = new TerminalThread();
//    }
//    if(cmdProcess == nullptr){
//        cmdProcess = new QProcess(this);
//        terminalThread->setCmdProcess(cmdProcess);
//    }

//    terminalThread->start();


      cmdProcess->start("cmd");
      cmdProcess->waitForStarted();

}

void TerminalSysteam::closeTerminal()
{
    cmdProcess->close();
    cmdProcess->waitForFinished();
}

bool TerminalSysteam::sendCommand(QString &str)
{
    cmdProcess->write(str.toLocal8Bit());
    return true;
}

void TerminalSysteam::_on_recvCmdOut()
{
    QByteArray data = cmdProcess->readAllStandardOutput();
    QString utf8_str=QString::fromLocal8Bit(data);
    GlobalData::global_terminalWidget->addMsg(utf8_str);
}

void TerminalSysteam::_on_recvCmdError()
{
    QByteArray data = cmdProcess->readAllStandardError();
    QString utf8_str=QString::fromLocal8Bit(data);
    GlobalData::global_terminalWidget->addMsg(utf8_str);
}

