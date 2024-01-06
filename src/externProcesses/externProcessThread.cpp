
#include "externProcessThread.h"
//#include "../common/global_data.h"


ExternProcessThread::ExternProcessThread(QObject *parent)
    : QThread{parent}
{
    makeProcess = new MakeProcess();
    targetExeCmdProcess = new QProcess();
    cmakeProcess = new CmakeProcess();

    makeProcess->moveToThread(this);
    makeProcess->getProcess()->moveToThread(this);
    cmakeProcess->moveToThread(this);
    cmakeProcess->getProcess()->moveToThread(this);
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

    delete cmakeProcess;
    cmakeProcess = nullptr;

    targetExeCmdProcess->deleteLater();

    delete commendQueue;
    commendQueue = nullptr;
}

void ExternProcessThread::run()
{

    QString info = "";
    int code = 0;
    bool doflag = false;
    // 开启生成程序用的cmd窗口
    targetExeCmdProcess->start("cmd.exe");
    targetExeCmdProcess->waitForStarted();
    targetExeCmdProcess->write("chcp 65001\n");
    targetExeCmdProcess->waitForBytesWritten();

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
            }else if(commend.commendName == "cmakeProcessConfig"){
                cmakeProcessConfigHandel(commend, &code);
                doflag = true;
            }else if(commend.commendName == "cmakeBuild"){
                cmakeBuildHandel(commend, &code);
                doflag = true;
            }else if(commend.commendName == "cmakeInstall"){
                cmakeInstallHandel(commend, &code);
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
    QString makeExePath;
    QString mkFileDir;
    QString mkFileName;
    if(commend.paramMap.contains("makeExePath")){
        makeExePath = commend.paramMap["makeExePath"];
    }
    if(commend.paramMap.contains("mkFileDir")){
        mkFileDir = commend.paramMap["mkFileDir"];
    }
    if(commend.paramMap.contains("mkFileName")){
        mkFileName = commend.paramMap["mkFileName"];
    }

    if(makeProcess->make(makeExePath,mkFileDir,mkFileName)){
        *code = 0;
    }else{
        *code = -1;
    }
}

void ExternProcessThread::cleanHandel(CommendStr &commend, int* code)
{
    QString makeExePath;
    QString mkFileDir;
    QString mkFileName;
    if(commend.paramMap.contains("makeExePath")){
        makeExePath = commend.paramMap["makeExePath"];
    }
    if(commend.paramMap.contains("mkFileDir")){
        mkFileDir = commend.paramMap["mkFileDir"];
    }
    if(commend.paramMap.contains("mkFileName")){
        mkFileName = commend.paramMap["mkFileName"];
    }
    if(makeProcess->clean(makeExePath,mkFileDir,mkFileName)){
        *code = 0;
    }else{
        *code = -1;
    }
}

void ExternProcessThread::cmakeProcessConfigHandel(CommendStr &commend, int *code)
{
    QString cComplierPath;
    QString cxxComplierPath;
    QString CMakePath = "";
    QString CMakeFilePath = "";
    QString buildDir = "";
    QString installDir = "";
    QString buildsystem = "";
    QString buildsystemPath = "";

    if(commend.paramMap.contains("cComplierPath")){
        cComplierPath = commend.paramMap["cComplierPath"];
    }
    if(commend.paramMap.contains("cxxComplierPath")){
        cxxComplierPath = commend.paramMap["cxxComplierPath"];
    }
    if(commend.paramMap.contains("CMakePath")){
        CMakePath = commend.paramMap["CMakePath"];
    }
    if(commend.paramMap.contains("CMakeFilePath")){
        CMakeFilePath = commend.paramMap["CMakeFilePath"];
    }
    if(commend.paramMap.contains("buildDir")){
        buildDir = commend.paramMap["buildDir"];
    }
    if(commend.paramMap.contains("installDir")){
        installDir = commend.paramMap["installDir"];
    }
    if(commend.paramMap.contains("buildsystem")){
        buildsystem = commend.paramMap["buildsystem"];
    }
    if(commend.paramMap.contains("buildsystemPath")){
        buildsystemPath = commend.paramMap["buildsystemPath"];
    }

    CmakeProcess::Cmake_Param cmakeParam = {
        CMakePath,
        CMakeFilePath,
        buildDir,
        installDir,
        buildsystem,
        buildsystemPath,
        cComplierPath,
        cxxComplierPath,
    };
    cmakeProcess->setCmakeParam(cmakeParam);

    *code = 0;
}

void ExternProcessThread::cmakeBuildHandel(CommendStr &commend, int *code)
{

    if(cmakeProcess->build()){
        *code = 0;
    }else{
        *code = -1;
    }
}

void ExternProcessThread::cmakeInstallHandel(CommendStr &commend, int *code)
{
    if(cmakeProcess->install()){
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

CmakeProcess *ExternProcessThread::getCmakeProcess() const
{
    return cmakeProcess;
}

void ExternProcessThread::setCmakeProcess(CmakeProcess *newCmakeProcess)
{
    cmakeProcess = newCmakeProcess;
}




