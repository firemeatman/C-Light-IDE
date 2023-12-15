
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
    GlobalData::ComplierPath = settings.value("complierPath","").toString();
    GlobalData::setMakeProgramPath(settings.value("makeProgramPath","").toString());
    GlobalData::setMakeFilePath(settings.value("makeFilePath","").toString());
    GlobalData::setDebugerPath(settings.value("debugerPath","").toString());
    settings.endGroup();

    //为了跨线程在信号中传递自定义参数，为其注册元数据类型
    qRegisterMetaType<QString>("QString&");//注册QString的引用

    GlobalData::codeFileSys = new CodeFileSys();
    GlobalData::ExternProcessThread = new ExternProcessThread();
    GlobalData::ExternProcessThread->moveToThread(GlobalData::ExternProcessThread);
    GlobalData::ExternProcessThread->start();

}

void save_data(){
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.beginGroup("gengerateSetting");
    settings.setValue("complierPath",GlobalData::ComplierPath);
    settings.setValue("makeProgramPath",GlobalData::getMakeProgramPath());
    settings.setValue("makeFilePath",GlobalData::getMakeFilePath());
    settings.setValue("debugerPath",GlobalData::getDebugerPath());
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

