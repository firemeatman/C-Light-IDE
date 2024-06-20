
#include <QApplication>
#include <QSettings>
#include <QMetaType>

#include "GUI/window/mainWindow/mainwindow.h"
#include "common/global_data.h"
#include "externProcesses/externProcessThread.h"


void init_app();
void save_data();
void relase_resouse();
void relase_mainWindow();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    init_app();
    int flag = a.exec();

    relase_mainWindow();
    save_data();
    relase_resouse();
    return flag;
}

void init_app(){


    // 继承QThread实现线程要记住更改所属的线程，包括构造函数中的。可能导致不同线程下new对象产生警告
    GlobalData::ExternProcessThread = new ExternProcessThread();
    GlobalData::ExternProcessThread->moveToThread(GlobalData::ExternProcessThread);
    GlobalData::ExternProcessThread->start();

    GlobalData::projectManager = new ProjectManager();
    GlobalData::editCodeManager = new EditCodeManager();

    // 为了跨线程在信号中传递自定义参数，为其注册元数据类型
    qRegisterMetaType<QString>("QString&");//注册QString的引用

    // 读取配置
    QSettings settings("config.ini", QSettings::IniFormat);

    settings.beginGroup("lastChoices");
    GlobalData::lastChoices.createProjectPath = settings.value("createProjectPath", "").toString();
    GlobalData::lastChoices.openProjectPath = settings.value("openProjectPath", "").toString();
    settings.endGroup();

    settings.beginGroup("history");
    int size = settings.beginReadArray("projectHistory");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        QString name = settings.value("name").toString();
        QString path= settings.value("path").toString();
        HistoryProject item = {name, path};
        GlobalData::historyProjectList.append(item);
    }
    settings.endArray();
    settings.endGroup();

    GlobalData::mainWindow = new MainWindow();
    GlobalData::mainWindow->show();
}

void save_data(){

    QSettings settings("config.ini", QSettings::IniFormat);

    settings.beginGroup("lastChoices");
    settings.setValue("createProjectPath", GlobalData::lastChoices.createProjectPath);
    settings.setValue("openProjectPath", GlobalData::lastChoices.openProjectPath);
    settings.endGroup();

    settings.beginGroup("history");
    settings.beginWriteArray("projectHistory");
    int size = GlobalData::historyProjectList.count();
    qDebug()<<"save size: "<<size;
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        settings.setValue("name", GlobalData::historyProjectList.at(i).name);
        settings.setValue("path", GlobalData::historyProjectList.at(i).rootPath);
    }
    settings.endArray();
    settings.endGroup();

}

void relase_resouse(){

    GlobalData::ExternProcessThread->requestInterruption();

    SAFE_DELE_P(GlobalData::projectManager);
    SAFE_DELE_P(GlobalData::editCodeManager);
    SAFE_DELE_P(GlobalData::ExternProcessThread);
}

void relase_mainWindow()
{
    SAFE_DELE_P(GlobalData::mainWindow);
}

