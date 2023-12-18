
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QToolBar>
#include <QLayout>
#include <QDockWidget>
#include <QToolButton>
#include <QMap>
#include "../common/global_data.h"

#include "sideMenu/sideMenuWidget.h"
#include "startPage/startPageWidget.h"
#include "codePage/codePageEditWidget.h"
#include "codePage/codeTreeSideWidget.h"
#include "codePage/codeFileListWidget.h"
#include "generatePage/generatePageWidget.h"
#include "infoWindow/makeInfoWidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 侧边菜单
    sideMenuWidget = new SideMenuWidget(this);
    QToolBar* toolBar = new QToolBar(this);
    toolBar->addWidget(sideMenuWidget);
    toolBar->setMovable(false);
    toolBar->setStyleSheet("QToolBar{border:0px solid white;}");
    toolBar->setFixedWidth(70);
    this->addToolBar(Qt::LeftToolBarArea, toolBar);

    // 初始化主要窗口
    startPageWidget = new StartPageWidget(this);
    codePageEditWidget = new CodePageEditWidget(this);
    codeTreeSideWidget = new CodeTreeSideWidget(this);
    codeFileListWidget = new CodeFileListWidget(this);
    generatePageWidget = new GeneratePageWidget(this);
    makeInfoWidget = new MakeInfoWidget(this);

    // 初始化dockwidget
    codeTreeSidedockWidget = new QDockWidget(this);
    makeOutdockWidget = new QDockWidget(this);
    codeFileListdockWidget = new QDockWidget(this);

    codeTreeSidedockWidget->setWidget(codeTreeSideWidget);
    codeTreeSidedockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    makeOutdockWidget->setWidget(makeInfoWidget);
    makeOutdockWidget->setFeatures(QDockWidget::DockWidgetClosable);
    //makeOutdockWidget->setTitleBarWidget(new QWidget(makeOutdockWidget));
    codeFileListdockWidget->setWidget(codeFileListWidget);
    codeFileListdockWidget->setFloating(false);
    //codeTreeSidedockWidget->resize();

    codePageEditWidget->hide();
    codeTreeSidedockWidget->hide();
    codeFileListdockWidget->hide();
    generatePageWidget->hide();
    makeOutdockWidget->hide();

    // 设置主窗口、dock窗口设置
    this->setCentralWidget(startPageWidget);
    this->setDockNestingEnabled(true);
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

    //===============================信号===========================================

    // 主窗口整体信号连接
    connect(sideMenuWidget->StartBtn , &QToolButton::clicked, this, &MainWindow::_on_clicked_StartBtn);
    connect(sideMenuWidget->CodeBtn , &QToolButton::clicked, this, &MainWindow::_on_clicked_CodeBtn);
    connect(sideMenuWidget->GenerateBtn , &QToolButton::clicked, this, &MainWindow::_on_clicked_GenerateBtn);
    connect(this->makeOutBtn, &QPushButton::clicked, this, &MainWindow::_on_clicked_makeOutBtn);

    // GUI部件之间的信号连接
    connect(codeTreeSideWidget->getTreeMenu(), &TreeMenu::openFileSignal,
            codeFileListWidget, &CodeFileListWidget::_on_openFile);
    connect(codeFileListWidget, &CodeFileListWidget::showFileData, codePageEditWidget, &CodePageEditWidget::setTextData);
    connect(codeFileListWidget, &CodeFileListWidget::switchFile, codePageEditWidget, &CodePageEditWidget::writeContentToCache);
    // 外部程序相关信号连接
    connect(GlobalData::ExternProcessThread->getMakeProcess(), &MakeProcess::msgRecved, makeInfoWidget, &MakeInfoWidget::addMsg);
    connect(GlobalData::ExternProcessThread, &ExternProcessThread::taskComplete, makeInfoWidget, &MakeInfoWidget::_on_makeCompleted);
    connect(GlobalData::ExternProcessThread, &ExternProcessThread::taskStart, makeInfoWidget, &MakeInfoWidget::_on_makeStart);
    connect(GlobalData::ExternProcessThread, &ExternProcessThread::taskComplete, sideMenuWidget, &SideMenuWidget::_on_runBtnTaskComplete);
}
MainWindow::~MainWindow()
{
    delete ui;
}

QDockWidget *MainWindow::getCodeTreeSidedockWidget() const
{
    return codeTreeSidedockWidget;
}

QDockWidget *MainWindow::getMakeOutdockWidget() const
{
    return makeOutdockWidget;
}

QDockWidget *MainWindow::getCodeFileListdockWidget() const
{
    return codeFileListdockWidget;
}

SideMenuWidget *MainWindow::getSideMenuWidget() const
{
    return sideMenuWidget;
}

StartPageWidget *MainWindow::getStartPageWidget() const
{
    return startPageWidget;
}

CodePageEditWidget *MainWindow::getCodePageEditWidget() const
{
    return codePageEditWidget;
}

CodeTreeSideWidget *MainWindow::getCodeTreeSideWidget() const
{
    return codeTreeSideWidget;
}

CodeFileListWidget *MainWindow::getCodeFileListWidget() const
{
    return codeFileListWidget;
}

MakeInfoWidget *MainWindow::getMakeInfoWidget() const
{
    return makeInfoWidget;
}

GeneratePageWidget *MainWindow::getGeneratePageWidget() const
{
    return generatePageWidget;
}

QPushButton *MainWindow::getProgramOutBtn() const
{
    return programOutBtn;
}

QPushButton *MainWindow::getMakeOutBtn() const
{
    return makeOutBtn;
}



void MainWindow::_on_clicked_StartBtn()
{
    this->takeCentralWidget();
    this->setCentralWidget(startPageWidget);
    if(codeTreeSidedockWidget != nullptr){
        this->removeDockWidget(codeTreeSidedockWidget);

    }
    if(makeOutdockWidget != nullptr){
        this->removeDockWidget(makeOutdockWidget);
    }
    if(codeFileListdockWidget != nullptr){
        this->removeDockWidget(codeFileListdockWidget);
    }
}

void MainWindow::_on_clicked_CodeBtn()
{
    this->takeCentralWidget();
    this->setCentralWidget(codePageEditWidget);
    this->addDockWidget(Qt::LeftDockWidgetArea, codeTreeSidedockWidget);
    this->splitDockWidget(codeTreeSidedockWidget,codeFileListdockWidget,Qt::Horizontal);
    this->addDockWidget(Qt::BottomDockWidgetArea, makeOutdockWidget);
    codePageEditWidget->show();
    codeTreeSidedockWidget->show();
    codeFileListdockWidget->show();
    //terminaldockWidget->show();
}

void MainWindow::_on_clicked_GenerateBtn()
{
    this->takeCentralWidget();
    this->setCentralWidget(generatePageWidget);
    if(codeTreeSidedockWidget != nullptr){
        this->removeDockWidget(codeTreeSidedockWidget);
    }
    if(makeOutdockWidget != nullptr){
        this->removeDockWidget(makeOutdockWidget);
    }
    if(codeFileListdockWidget != nullptr){
        this->removeDockWidget(codeFileListdockWidget);
    }
    generatePageWidget->show();
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




