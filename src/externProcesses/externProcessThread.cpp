
#include "externProcessThread.h"
#include "../common/global_data.h"


ExternProcessThread::ExternProcessThread(QObject *parent)
    : QThread{parent}
{
    makeProcess = new MakeProcess();
    targetExeCmdProcess = new QProcess();
    makeProcess->moveToThread(this);
    makeProcess->getProcess()->moveToThread(this);
    targetExeCmdProcess->moveToThread(this);

    commendQueue = new BlockingQueue<CommendStr>();

}

ExternProcessThread::~ExternProcessThread()
{
    if(this->isRunning() || !this->isFinished()){
        // 请求终止
        requestInterruption();
        wait();
    }

    delete makeProcess;
    makeProcess = nullptr;


    targetExeCmdProcess->deleteLater();

    delete commendQueue;
    commendQueue = nullptr;
}

void ExternProcessThread::run()
{

    QString info = "";
    int code = 0;
    targetExeCmdProcess->start("cmd.exe");
    targetExeCmdProcess->waitForStarted();
    forever{
        if(this->isInterruptionRequested()){
            break;
        }
        if(!commendQueue->isEmpty()){
            CommendStr commend = commendQueue->take();
            if(commend.commendName == makeCommend){
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
            }else if(commend.commendName == "run target"){
                QString writeStr;
                QString workpath;
                QString exeName;
                if(commend.paramMap.contains("workpath")){
                    workpath = commend.paramMap["workpath"];
                }
                if(commend.paramMap.contains("exeName")){
                    exeName = commend.paramMap["exeName"];
                }
                writeStr = "cd ";
                writeStr.append(workpath).append(" && start ").append(exeName).append("\n");
                targetExeCmdProcess->write(writeStr.toLocal8Bit());
            }
        }
        msleep(100); // ms。sleep是秒
    }

    targetExeCmdProcess->close();
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

BlockingQueue<ExternProcessThread::CommendStr> *ExternProcessThread::getCommendQueue() const
{
    return commendQueue;
}

void ExternProcessThread::setCommendQueue(BlockingQueue<ExternProcessThread::CommendStr> *newCommendQueue)
{
    commendQueue = newCommendQueue;
}


