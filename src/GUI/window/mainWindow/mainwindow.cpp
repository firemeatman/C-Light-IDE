
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QToolBar>
#include <QLayout>
#include <QDockWidget>
#include <QToolButton>
#include <QMap>
#include "../../../common/global_data.h"

#include "sideMenu/sideMenuWidget.h"
#include "../../page/startPage/startPageWidget.h"
#include "../../page/codePage/codePage.h"
#include "../../page/codePage/codePageEditWidget.h"
#include "../../page/codePage/codeTreeSideWidget.h"
#include "../../page/codePage/codeFileListWidget.h"
#include "../../page/configPage/projectConfigSideMenu.h"
#include "../../page/configPage/projectConfigWidget.h"
#include "../../page/configPage/genBuildConfigWidget.h"
#include "../../page/configPage/debugConfigWidget.h"
#include "../infoWindow/makeInfoWidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setDockNestingEnabled(true);

    //===============================主窗口部件初始化====================================

    // 侧边菜单
    sideMenuWidget = new SideMenuWidget(this);
    QToolBar* toolBar = new QToolBar(this);
    toolBar->addWidget(sideMenuWidget);
    toolBar->setMovable(false);
    toolBar->setStyleSheet("QToolBar{border:0px solid white;}");
    toolBar->setFixedWidth(70);
    this->addToolBar(Qt::LeftToolBarArea, toolBar);

    // ---信息窗口
    makeInfoWidget = new MakeInfoWidget(this);
    makeOutdockWidget = new QDockWidget(this);
    makeOutdockWidget->setWidget(makeInfoWidget);
    makeOutdockWidget->setFeatures(QDockWidget::DockWidgetClosable);
    makeOutdockWidget->hide();
    this->addDockWidget(Qt::BottomDockWidgetArea, makeOutdockWidget);
    //makeOutdockWidget->setTitleBarWidget(new QWidget(makeOutdockWidget));

    // 设置状态栏
    this->programOutBtn = new QPushButton(this);
    this->makeOutBtn = new QPushButton(this);
    QWidget* spacer = new QWidget(this);
    programOutBtn->setText("程序输出");
    makeOutBtn->setText("make输出");
    spacer->setFixedWidth(70);
    this->statusBar()->setSizeGripEnabled(false); //去掉状态栏右下角的三角
    this->statusBar()->addWidget(spacer);
    this->statusBar()->addWidget(programOutBtn);
    this->statusBar()->addWidget(makeOutBtn);

    //============================初始化页面=================================
    // 页面管理器
    stackWidget = new QStackedWidget(this);
    this->setCentralWidget(stackWidget);

    // ---开始页面
    startPageWidget = new StartPageWidget(this);
    stackWidget->addWidget(startPageWidget); // 0
    // ---代码窗口
    codePage = new CodePage(this);
    stackWidget->addWidget(codePage); // 1

    // ---配置窗口
    // projectConfigSideMenu = new ProjectConfigSideMenu(this);
    // projectConfigWidget = new ProjectConfigWidget(this);
    // genBuildConfigWidget = new GenBuildConfigWidget(this);
    // _debugConfigWidget = new debugConfigWidget(this);
    // projectConfigSideMenuDockWidget = new QDockWidget(this);
    // projectConfigWidget->hide();
    // genBuildConfigWidget->hide();
    // _debugConfigWidget->hide();
    // projectConfigSideMenuDockWidget->setWidget(projectConfigSideMenu);
    // projectConfigSideMenuDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    // projectConfigSideMenuDockWidget->hide();
    // page_p = new Page(WindowPageRoute::ConfigPage, codePageEditWidget);
    // page_p->addDock(projectConfigSideMenuDockWidget, false);
    // this->pageList.append(page_p);


    //===============================信号===========================================

    // 主窗口部件信号连接
    connect(this->makeOutBtn, &QPushButton::clicked, this, &MainWindow::_on_clicked_makeOutBtn);

    // GUI部件之间的信号连接
    // connect(codeTreeSideWidget->getTreeMenu(), &TreeMenu::openFileSignal,
    //         codeFileListWidget, &CodeFileListWidget::_on_openFile);
    // connect(codeFileListWidget, &CodeFileListWidget::switchFile, codePageEditWidget, &CodePageEditWidget::_on_switchFile);
    // 外部程序相关信号连接
    connect(GlobalData::ExternProcessThread->getMakeProcess(), &MakeProcess::msgRecved, makeInfoWidget, &MakeInfoWidget::addMsg);
    connect(GlobalData::ExternProcessThread->getCmakeProcess(), &CmakeProcess::msgRecved, makeInfoWidget, &MakeInfoWidget::addMsg);
    connect(GlobalData::ExternProcessThread, &ExternProcessThread::taskComplete, makeInfoWidget, &MakeInfoWidget::_on_makeCompleted);
    connect(GlobalData::ExternProcessThread, &ExternProcessThread::taskStart, makeInfoWidget, &MakeInfoWidget::_on_makeStart);
    connect(GlobalData::ExternProcessThread, &ExternProcessThread::taskComplete, sideMenuWidget, &SideMenuWidget::_on_runBtnTaskComplete);

    // connect(GlobalData::projectSys, &ProjectSys::projectLoaded, projectConfigWidget, &ProjectConfigWidget::_on_projectLoaded);
    // connect(GlobalData::projectSys, &ProjectSys::projectLoaded, genBuildConfigWidget, &GenBuildConfigWidget::_on_projectLoaded);
    // connect(GlobalData::projectSys, &ProjectSys::projectLoaded, _debugConfigWidget, &debugConfigWidget::_on_projectLoaded);

}
MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::jump(WindowPageRoute route, QVariantMap &param)
{
    bool flag = true;

    switch (route) {
    case WindowPageRoute::StartPage:
    {
        this->stackWidget->setCurrentWidget(this->startPageWidget);
        break;
    }
    case WindowPageRoute::CodePage:
    {
        this->stackWidget->setCurrentWidget(this->codePage);
        break;
    }
    case WindowPageRoute::ConfigPage:
    {
        break;
    }
    default:
        flag = false;
        break;
    }

    if(flag){
        emit pageSwitched(route, param);
    }
    return flag;

}

void MainWindow::_on_clicked_programOutBtn()
{

}


void MainWindow::_on_clicked_makeOutBtn()
{
    if(this->makeOutdockWidget->isHidden()){
        this->addDockWidget(Qt::BottomDockWidgetArea,makeOutdockWidget);
        this->makeOutdockWidget->show();
    }else{
        this->removeDockWidget(makeOutdockWidget);
    }
}
