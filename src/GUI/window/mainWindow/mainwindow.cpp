
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
    // ---开始页面
    startPageWidget = new StartPageWidget(this);
    Page* page_p = new Page(WindowPageRoute::StartPage, startPageWidget);
    this->pageList.append(page_p);

    // ---代码窗口
    codePageEditWidget = new CodePageEditWidget(this);
    codeTreeSideWidget = new CodeTreeSideWidget(this);
    codeFileListWidget = new CodeFileListWidget(this);
    codeTreeSidedockWidget = new QDockWidget(this);
    codeFileListdockWidget = new QDockWidget(this);
    codePageEditWidget->hide();
    codeTreeSidedockWidget->setWidget(codeTreeSideWidget);
    codeTreeSidedockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    codeTreeSidedockWidget->hide();
    codeFileListdockWidget->setWidget(codeFileListWidget);
    codeFileListdockWidget->setFloating(false);
    codeFileListdockWidget->hide();

    page_p = new Page(WindowPageRoute::CodePage, codePageEditWidget);
    page_p->addDock(codeTreeSidedockWidget, false);
    page_p->addDock(codeFileListdockWidget, false);
    this->pageList.append(page_p);

    // ---配置窗口
    projectConfigSideMenu = new ProjectConfigSideMenu(this);
    projectConfigWidget = new ProjectConfigWidget(this);
    genBuildConfigWidget = new GenBuildConfigWidget(this);
    _debugConfigWidget = new debugConfigWidget(this);
    projectConfigSideMenuDockWidget = new QDockWidget(this);
    projectConfigWidget->hide();
    genBuildConfigWidget->hide();
    _debugConfigWidget->hide();
    projectConfigSideMenuDockWidget->setWidget(projectConfigSideMenu);
    projectConfigSideMenuDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    projectConfigSideMenuDockWidget->hide();
    page_p = new Page(WindowPageRoute::ConfigPage, codePageEditWidget);
    page_p->addDock(projectConfigSideMenuDockWidget, false);
    this->pageList.append(page_p);

    // 设置起始页面
    this->setCentralWidget(startPageWidget);

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
    for(auto p : this->pageList){
        SAFE_DELE_P(p);
    }
    delete ui;
}

bool MainWindow::jump(WindowPageRoute route, QVariantMap &param)
{
    bool flag = true;
    this->takeCentralWidget();

    // 移除其他页面的dock；设置主部件
    int size = this->pageList.size();
    Page* page_p = nullptr;
    for(int i=0; i<size;i++){
        page_p = pageList[i];
        if(route == page_p->routeName){
            this->setCentralWidget(page_p->centralWindow);
            page_p->centralWindow->show();
            continue;
        }

        for(auto docInfo : page_p->dockList){
            this->removeDockWidget(docInfo.dock_p);
        }
    }

    // 添加dock
    switch (route) {
    case WindowPageRoute::StartPage:
    {
        break;
    }
    case WindowPageRoute::CodePage:
    {
        this->addDockWidget(Qt::LeftDockWidgetArea, codeTreeSidedockWidget);
        this->splitDockWidget(codeTreeSidedockWidget,codeFileListdockWidget,Qt::Horizontal);
        codeTreeSidedockWidget->show();
        codeFileListdockWidget->show();
        break;
    }
    case WindowPageRoute::ConfigPage:
    {
        this->addDockWidget(Qt::LeftDockWidgetArea, projectConfigSideMenuDockWidget);
        projectConfigSideMenuDockWidget->show();
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


Page::Page(WindowPageRoute route, QWidget *centralWindow)
{
    this->routeName = route;
    this->centralWindow = centralWindow;
}

void Page::addDock(QDockWidget *dock, bool state)
{
    DockInfo dockInfo;
    dockInfo.dock_p = dock;
    dockInfo.settedState = state;
    this->dockList.append(dockInfo);
}
