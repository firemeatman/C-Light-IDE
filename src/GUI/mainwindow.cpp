
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QToolBar>
#include <QLayout>
#include <QDockWidget>
#include <QToolButton>

#include "sideMenu/sideMenuWidget.h"
#include "startPage/startPageWidget.h"
#include "codePage/codePageEditWidget.h"
#include "codePage/codeTreeSideWidget.h"
#include "codePage/codeFileListWidget.h"
#include "generatePage/generatePageWidget.h"
#include "commonWidget/terminalWidget.h"

#include "../common/global_data.h"

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
    //toolBar->setFixedWidth(50);
    this->addToolBar(Qt::LeftToolBarArea, toolBar);
    // 初始化主要窗口
    startPageWidget = new StartPageWidget(this);
    codePageEditWidget = new CodePageEditWidget(this);
    codeTreeSideWidget = new CodeTreeSideWidget(this);
    terminalWidget = new TerminalWidget(this);
    codeFileListWidget = new CodeFileListWidget(this);
    generatePageWidget = new GeneratePageWidget(this);
    GlobalData::global_terminalWidget = terminalWidget;

    // 初始化dockwidget
    codeTreeSidedockWidget = new QDockWidget(this);
    terminaldockWidget = new QDockWidget(this);
    codeFileListdockWidget = new QDockWidget(this);

    codeTreeSidedockWidget->setWidget(codeTreeSideWidget);
    codeTreeSidedockWidget->setFloating(false);
    terminaldockWidget->setWidget(terminalWidget);
    terminaldockWidget->setFloating(false);
    codeFileListdockWidget->setWidget(codeFileListWidget);
    codeFileListdockWidget->setFloating(false);
    //codeTreeSidedockWidget->resize();

    codePageEditWidget->hide();
    codeTreeSidedockWidget->hide();
    codeFileListdockWidget->hide();
    generatePageWidget->hide();
    terminaldockWidget->hide();

    this->setCentralWidget(startPageWidget);

    this->setDockNestingEnabled(true);

//    codeTreeSideWidget->getTreeMenu()->getNewDirWidget()->setParent(this);
//    codeTreeSideWidget->getTreeMenu()->getNewFileWidget()->setParent(this);

    connect(sideMenuWidget->StartBtn , &QToolButton::clicked, this, &MainWindow::_on_clicked_StartBtn);
    connect(sideMenuWidget->CodeBtn , &QToolButton::clicked, this, &MainWindow::_on_clicked_CodeBtn);
    connect(sideMenuWidget->GenerateBtn , &QToolButton::clicked, this, &MainWindow::_on_clicked_GenerateBtn);
    connect(sideMenuWidget->RunBtn , &QToolButton::clicked, this, &MainWindow::_on_clicked_RunBtn);

    connect(codeTreeSideWidget->getTreeMenu(), &TreeMenu::openFileSignal,
            codeFileListWidget, &CodeFileListWidget::_on_openFile);
    connect(codeFileListWidget, &CodeFileListWidget::showFileData, codePageEditWidget, &CodePageEditWidget::setTextData);
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
    if(terminaldockWidget != nullptr){
        this->removeDockWidget(terminaldockWidget);
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
    this->addDockWidget(Qt::BottomDockWidgetArea, terminaldockWidget);
    codePageEditWidget->show();
    codeTreeSidedockWidget->show();
    codeFileListdockWidget->show();
    terminaldockWidget->show();
}

void MainWindow::_on_clicked_GenerateBtn()
{
    this->takeCentralWidget();
    this->setCentralWidget(generatePageWidget);
    if(codeTreeSidedockWidget != nullptr){
        this->removeDockWidget(codeTreeSidedockWidget);
    }
    if(terminaldockWidget != nullptr){
        this->removeDockWidget(terminaldockWidget);
    }
    if(codeFileListdockWidget != nullptr){
        this->removeDockWidget(codeFileListdockWidget);
    }
    generatePageWidget->show();
}

void MainWindow::_on_clicked_RunBtn()
{

    QString str("dir\n");
    GlobalData::global_terminalSysteam->sendCommand(str);
}


