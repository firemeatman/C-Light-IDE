
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
    bool doflag = false;
    targetExeCmdProcess->start("cmd.exe");
    targetExeCmdProcess->waitForStarted();
    forever{
        if(this->isInterruptionRequested()){
            break;
        }
        if(!commendQueue->isEmpty()){
            CommendStr commend = commendQueue->take();
            emit taskStart(commend.commendName, commend.from);

            if(commend.commendName == "make"){    
                makeHandel(commend, &code);
                doflag = true;
            }else if(commend.commendName == "clean"){
                cleanHandel(commend, &code);
                doflag = true;
            }else if(commend.commendName == "run target"){
                runTargetHandel(commend, &code);
                doflag = true;
            }
            if(!doflag){
                code = -2;
                info = "系统错误!";
            }
            emit taskComplete(commend.commendName, code, info, commend.from);
            doflag = false;
        }
        msleep(100); // ms。sleep是秒
    }

    targetExeCmdProcess->close();
    return;

}

void ExternProcessThread::makeHandel(CommendStr &commend, int* code)
{
    QString makeExePath = GlobalData::getMakeProgramPath();
    QString mkFilePath = GlobalData::getMakeFilePath();
    QString fileName = "";
    if(makeProcess->make(makeExePath,mkFilePath,fileName)){
        *code = 0;
    }else{
        *code = -1;
    }
}

void ExternProcessThread::cleanHandel(CommendStr &commend, int* code)
{
    QString makeExePath;
    QString mkFilePath;
    QString fileName = "";
    if(commend.paramMap.contains("makeExePath")){
        makeExePath = commend.paramMap["makeExePath"];
    }
    if(commend.paramMap.contains("mkFilePath")){
        mkFilePath = commend.paramMap["mkFilePath"];
    }
    if(commend.paramMap.contains("fileName")){
        fileName = commend.paramMap["fileName"];
    }
    if(makeProcess->clean(makeExePath,mkFilePath,fileName)){
        *code = 0;
    }else{
        *code = -1;
    }
}

void ExternProcessThread::runTargetHandel(CommendStr &commend, int* code)
{
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
    targetExeCmdProcess->waitForBytesWritten(3000);
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




