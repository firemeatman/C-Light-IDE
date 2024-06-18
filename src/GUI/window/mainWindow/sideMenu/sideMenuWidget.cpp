#include "sideMenuWidget.h"
#include "ui_sideMenuWidget.h"
#include <QStyle>
#include <QFile>
#include <QFileInfo>
#include <QDockWidget>
#include "../../../../common/global_data.h"

SideMenuWidget::SideMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideMenuWidget)
{
    ui->setupUi(this);

    StartBtn = ui->toolButton;
    CodeBtn = ui->toolButton_2;
    ConfigBtn = ui->toolButton_4;
    RunBtn = ui->toolButton_5;


    //=========================信号连接=========================
    connect(StartBtn , &QToolButton::clicked, this, &SideMenuWidget::_on_clicked_StartBtn);
    connect(CodeBtn , &QToolButton::clicked, this, &SideMenuWidget::_on_clicked_CodeBtn);
    connect(ConfigBtn , &QToolButton::clicked, this, &SideMenuWidget::_on_clicked_ConfigBtn);
    connect(RunBtn, &QToolButton::clicked, this, &SideMenuWidget::_on_clicked_RunBtn);

}

SideMenuWidget::~SideMenuWidget()
{
    delete ui;
}

void SideMenuWidget::_on_clicked_StartBtn()
{
    QVariantMap param;
    GlobalData::mainWindow->jump(WindowPageRoute::StartPage, param);
}

void SideMenuWidget::_on_clicked_CodeBtn()
{
    QVariantMap param;
    GlobalData::mainWindow->jump(WindowPageRoute::CodePage, param);
}

void SideMenuWidget::_on_clicked_ConfigBtn()
{
    QVariantMap param;
    GlobalData::mainWindow->jump(WindowPageRoute::ConfigPage, param);
}

void SideMenuWidget::_on_clicked_RunBtn()
{
    // BlockingQueue<ExternProcessThread::CommendStr>* commendQueue = GlobalData::ExternProcessThread->getCommendQueue();
    // ExternProcessThread::CommendStr commendStr;
    // QMap<QString, QString> params;

    // ProjectConfig* project = GlobalData::projectSys->getCurrentProject();
    // if(project == nullptr){
    //     return;
    // }
    // if(project->projectType == CMAKE_PROJECT){
    //     params.insert("cComplierPath", project->cmakeConfig.c_ComplierPath);
    //     params.insert("cxxComplierPath", project->cmakeConfig.cxx_ComplierPath);
    //     params.insert("CMakePath", project->cmakeConfig.CMakePath);
    //     params.insert("CMakeFilePath", project->cmakeConfig.CMakeFilePath);
    //     params.insert("buildDir", project->cmakeConfig.buildDir);
    //     params.insert("installDir", project->cmakeConfig.installDir);
    //     if(project->cmakeConfig.buildsystem == Buildsystem_Type::Ninja){
    //         params.insert("buildsystem", "Ninja");
    //     }
    //     params.insert("buildsystemPath", project->cmakeConfig.buildsystemPath);

    //     commendStr.commendName = "cmakeProcessConfig";
    //     commendStr.from ="menuRunBtn";
    //     commendStr.paramMap = params;
    // }else if(project->projectType == MAKEFILE_PROJECT){

    // }

    // commendQueue->put(commendStr);

    // // 弹出make输出信息窗口
    // QDockWidget* makeoutDock = GlobalData::global_mainWindow->getMakeOutdockWidget();
    // GlobalData::global_mainWindow->addDockWidget(Qt::BottomDockWidgetArea,makeoutDock);
    // makeoutDock->show();

    // RunBtn->setDisabled(true);
}

void SideMenuWidget::_on_runBtnTaskComplete(QString &taskName, int code, QString &info, QString &from)
{
    // static QString ownName = "menuRunBtn";
    // if(from != ownName){
    //     return;
    // }
    // // 属于侧边菜单RUN按钮的任务状态机
    // if(taskName == "cmakeProcessConfig"){
    //     BlockingQueue<ExternProcessThread::CommendStr>* commendQueue = GlobalData::ExternProcessThread->getCommendQueue();
    //     ExternProcessThread::CommendStr commendStr;
    //     QMap<QString, QString> params;

    //     commendStr.commendName = "cmakeBuild";
    //     commendStr.from = ownName;
    //     commendStr.paramMap = params;
    //     commendQueue->put(commendStr);
    // }else if(taskName == "cmakeBuild"){
    //     BlockingQueue<ExternProcessThread::CommendStr>* commendQueue = GlobalData::ExternProcessThread->getCommendQueue();
    //     ExternProcessThread::CommendStr commendStr;
    //     QMap<QString, QString> params;

    //     commendStr.commendName = "cmakeInstall";
    //     commendStr.from = ownName;
    //     commendStr.paramMap = params;
    //     commendQueue->put(commendStr);
    // }else if(taskName == "cmakeInstall"){
    //     BlockingQueue<ExternProcessThread::CommendStr>* commendQueue = GlobalData::ExternProcessThread->getCommendQueue();
    //     ExternProcessThread::CommendStr commendStr;
    //     QMap<QString, QString> params;
    //     ProjectConfig* project = GlobalData::projectSys->getCurrentProject();
    //     if(project == nullptr){
    //         return;
    //     }
    //     params.insert("workpath", project->cmakeConfig.installDir);
    //     params.insert("exeName", project->projectName);

    //     commendStr.commendName = "run target";
    //     commendStr.from = ownName;
    //     commendStr.paramMap = params;
    //     commendQueue->put(commendStr);
    // }else if(taskName == "make"){
    //     BlockingQueue<ExternProcessThread::CommendStr>* commendQueue = GlobalData::ExternProcessThread->getCommendQueue();
    //     ExternProcessThread::CommendStr commendStr;
    //     QMap<QString, QString> params;
    //     params.insert("workpath", GlobalData::targetExeDir);
    //     params.insert("exeName", GlobalData::targetExeName);

    //     commendStr.commendName = "run target";
    //     commendStr.from = ownName;
    //     commendStr.paramMap = params;
    //     commendQueue->put(commendStr);
    // }else if(taskName == "run target"){
    //     RunBtn->setDisabled(false);
    // }
}




