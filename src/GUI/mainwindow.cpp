
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QToolBar>
#include <QLayout>
#include <QDockWidget>
#include <QToolButton>

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
    //toolBar->setFixedWidth(50);
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
    codeTreeSidedockWidget->setFloating(false);
    makeOutdockWidget->setWidget(makeInfoWidget);
    makeOutdockWidget->setFloating(false);
    codeFileListdockWidget->setWidget(codeFileListWidget);
    codeFileListdockWidget->setFloating(false);
    //codeTreeSidedockWidget->resize();

    codePageEditWidget->hide();
    codeTreeSidedockWidget->hide();
    codeFileListdockWidget->hide();
    generatePageWidget->hide();
    makeOutdockWidget->hide();

    // 设置主窗口、dock窗口设置、设置状态栏
    this->setCentralWidget(startPageWidget);
    this->setDockNestingEnabled(true);
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

//    codeTreeSideWidget->getTreeMenu()->getNewDirWidget()->setParent(this);
//    codeTreeSideWidget->getTreeMenu()->getNewFileWidget()->setParent(this);

    connect(sideMenuWidget->StartBtn , &QToolButton::clicked, this, &MainWindow::_on_clicked_StartBtn);
    connect(sideMenuWidget->CodeBtn , &QToolButton::clicked, this, &MainWindow::_on_clicked_CodeBtn);
    connect(sideMenuWidget->GenerateBtn , &QToolButton::clicked, this, &MainWindow::_on_clicked_GenerateBtn);
    connect(sideMenuWidget->RunBtn , &QToolButton::clicked, this, &MainWindow::_on_clicked_RunBtn);
    connect(this->makeOutBtn, &QPushButton::clicked, this, &MainWindow::_on_clicked_makeOutBtn);

    connect(codeTreeSideWidget->getTreeMenu(), &TreeMenu::openFileSignal,
            codeFileListWidget, &CodeFileListWidget::_on_openFile);
    connect(codeFileListWidget, &CodeFileListWidget::showFileData, codePageEditWidget, &CodePageEditWidget::setTextData);
    connect(codeFileListWidget, &CodeFileListWidget::switchFile, codePageEditWidget, &CodePageEditWidget::writeContentToCache);
    connect(GlobalData::ExternProcessThread->getMakeProcess(), &MakeProcess::msgRecved, makeInfoWidget, &MakeInfoWidget::addMsg);
    connect(GlobalData::ExternProcessThread, &ExternProcessThread::taskComplete, this, &MainWindow::_makeComplete);
}
MainWindow::~MainWindow()
{
    delete ui;
}

CodeTreeSideWidget *MainWindow::getCodeTreeSideWidget() const
{
    return codeTreeSideWidget;
}

CodeFileListWidget *MainWindow::getCodeFileListWidget() const
{
    return codeFileListWidget;
}

void MainWindow::setCodeFileListWidget(CodeFileListWidget *newCodeFileListWidget)
{
    codeFileListWidget = newCodeFileListWidget;
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
//    this->addDockWidget(Qt::LeftDockWidgetArea, codeFileListdockWidget);
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

void MainWindow::_on_clicked_RunBtn()
{   
    BlockingQueue<QString>* commendQueue = GlobalData::ExternProcessThread->getCommendQueue();
    commendQueue->put("make");
    sideMenuWidget->RunBtn->setDisabled(true);
}

void MainWindow::_on_clicked_programOutBtn()
{

}

void MainWindow::_on_clicked_makeOutBtn()
{

    this->addDockWidget(Qt::BottomDockWidgetArea,makeOutdockWidget);
    this->makeOutdockWidget->show();
}

void MainWindow::_makeComplete(QString &taskName, int code, QString &info){
    if(taskName == "make"){
        if(code == 0){
            qDebug()<<"make完成";
        }else{
            qDebug()<<"make失败";
        }
    }
    sideMenuWidget->RunBtn->setDisabled(false);
}


