
#include "externProcessThread.h"
#include "../common/global_data.h"


ExternProcessThread::ExternProcessThread(QObject *parent)
    : QThread{parent}
{
    makeProcess = new MakeProcess();
    commendQueue = new BlockingQueue<QString>();


}

ExternProcessThread::~ExternProcessThread()
{
    if(!this->isRunning() || !this->isFinished()){
        // 请求终止
        requestInterruption();
        wait();
    }

    delete makeProcess;
    makeProcess = nullptr;
    delete commendQueue;
    commendQueue = nullptr;
}

void ExternProcessThread::run()
{

    QString info = "";
    int code = 0;

    forever{
        if(this->isInterruptionRequested()){
            break;
        }
        if(!commendQueue->isEmpty()){
            QString commend = commendQueue->take();
            if(commend == makeCommend){
                QString makeExePath = GlobalData::getMakeProgramPath();
                QString mkFilePath = GlobalData::getMakeFilePath();
                QString fileName = "";
                if(makeProcess->make(makeExePath,mkFilePath,fileName)){
                    info = "";
                    code = 0;
                    emit taskComplete(makeCommend, code, info);
                }else{
                    code = -1;
                    emit taskComplete(makeCommend, code, info);
                }
            }
        }
        msleep(100); // ms。sleep是秒
    }

    return;

}

DebuggerProcess *ExternProcessThread::getDebuggerProcess() const
{
    return debuggerProcess;
}

void ExternProcessThread::setDebuggerProcess(DebuggerProcess *newDebuggerProcess)
{
    debuggerProcess = newDebuggerProcess;
}

MakeProcess *ExternProcessThread::getMakeProcess() const
{
    return makeProcess;
}

void ExternProcessThread::setMakeProcess(MakeProcess *newMakeProcess)
{
    makeProcess = newMakeProcess;
}

BlockingQueue<QString> *ExternProcessThread::getCommendQueue() const
{
    return commendQueue;
}

void ExternProcessThread::setCommendQueue(BlockingQueue<QString> *newCommendQueue)
{
    commendQueue = newCommendQueue;
}

