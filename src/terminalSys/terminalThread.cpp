
#include "terminalThread.h"
#include <QProcess>

#include "../common/global_data.h""

TerminalThread::TerminalThread()
{

}

void TerminalThread::run()
{
    while(1){
        queneMutex.lock();
        if(commondQueue.isEmpty()){
            continue;
            queneMutex.unlock();
        }
        QString commond = commondQueue.dequeue();

        queneMutex.unlock();

    }
}

void TerminalThread::addCommond(QString &str)
{
    queneMutex.lock();
    commondQueue.enqueue(str);
    queneMutex.unlock();
}

void TerminalThread::setCmdProcess(QProcess *cmdProcess)
{
    cmdMutex.lock();

    this->cmdProcess = cmdProcess;

    cmdMutex.unlock();
}

