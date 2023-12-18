
#include "./GUI/mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QMetaType>

#include "common/global_data.h"
#include "codeFileSys/codeFileSys.h"
#include "externProcesses/externProcessThread.h"

void init_app();
void save_data();
void relase_resouse();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    init_app();

    MainWindow w;
    GlobalData::global_mainWindow = &w;
    w.show();
    int flag = a.exec();

    save_data();
    relase_resouse();
    return flag;
}

void init_app(){

    // 读取配置
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.beginGroup("gengerateSetting");
    GlobalData::complierDir = settings.value("complierDir","").toString();
    GlobalData::makeExePath = settings.value("makeExePath","").toString();
    GlobalData::mainMakefilePath = settings.value("mainMakefilePath","").toString();
    GlobalData::mainMakefileDir = settings.value("mainMakefileDir","").toString();
    GlobalData::mainMakefileFullName = settings.value("mainMakefileFullName","").toString();
    GlobalData::targetExeDir = settings.value("targetExeDir","").toString();
    GlobalData::targetExeName = settings.value("targetExeName","").toString();
    GlobalData::debugerExePath = settings.value("debugerExePath","").toString();
    GlobalData::lastProjectDir = settings.value("lastProjectDir","").toString();
    settings.endGroup();

    // 为了跨线程在信号中传递自定义参数，为其注册元数据类型
    qRegisterMetaType<QString>("QString&");//注册QString的引用

    GlobalData::codeFileSys = new CodeFileSys();
    // 继承QThread实现线程要记住更改所属的线程，包括构造函数中的。可能导致不同线程下new对象产生警告
    GlobalData::ExternProcessThread = new ExternProcessThread();
    GlobalData::ExternProcessThread->moveToThread(GlobalData::ExternProcessThread);
    GlobalData::ExternProcessThread->start();

}

void save_data(){
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.beginGroup("gengerateSetting");
    settings.setValue("complierDir",GlobalData::complierDir);
    settings.setValue("makeExePath",GlobalData::makeExePath);
    settings.setValue("mainMakefilePath",GlobalData::mainMakefilePath);
    settings.setValue("mainMakefileDir",GlobalData::mainMakefileDir);
    settings.setValue("mainMakefileFullName",GlobalData::mainMakefileFullName);
    settings.setValue("targetExeDir",GlobalData::targetExeDir);
    settings.setValue("targetExeName",GlobalData::targetExeName);
    settings.setValue("debugerExePath",GlobalData::debugerExePath);
    settings.setValue("lastProjectDir",GlobalData::lastProjectDir);
    settings.endGroup();

}

void relase_resouse(){

    GlobalData::ExternProcessThread->requestInterruption();
    if(GlobalData::codeFileSys != nullptr){
        delete GlobalData::codeFileSys;
        GlobalData::codeFileSys = nullptr;
    }
    if(GlobalData::ExternProcessThread != nullptr){
        delete GlobalData::ExternProcessThread;
        GlobalData::ExternProcessThread = nullptr;
    }
}

