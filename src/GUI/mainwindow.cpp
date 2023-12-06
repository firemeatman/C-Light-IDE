
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
    //toolBar->setFixedWidth(50);
    this->addToolBar(Qt::LeftToolBarArea, toolBar);
    // 初始化主要窗口
    startPageWidget = new StartPageWidget(this);
    codePageEditWidget = new CodePageEditWidget(this);
    codeTreeSideWidget = new CodeTreeSideWidget(this);
    terminalWidget = new TerminalWidget(this);
    generatePageWidget = new GeneratePageWidget(this);
    GlobalData::global_terminalWidget = terminalWidget;

    // 初始化dockwidget
    codeTreeSidedockWidget = new QDockWidget(this);
    terminaldockWidget = new QDockWidget(this);


    codeTreeSidedockWidget->setWidget(codeTreeSideWidget);
    codeTreeSidedockWidget->setFloating(false);
    terminaldockWidget->setWidget(terminalWidget);
    terminaldockWidget->setFloating(false);
    //codeTreeSidedockWidget->resize();

    codePageEditWidget->hide();
    codeTreeSidedockWidget->hide();
    generatePageWidget->hide();
    terminaldockWidget->hide();
    this->setCentralWidget(startPageWidget);

    connect(sideMenuWidget->StartBtn , &QToolButton::clicked, this, &MainWindow::_on_clicked_StartBtn);
    connect(sideMenuWidget->CodeBtn , &QToolButton::clicked, this, &MainWindow::_on_clicked_CodeBtn);
    connect(sideMenuWidget->GenerateBtn , &QToolButton::clicked, this, &MainWindow::_on_clicked_GenerateBtn);
    connect(sideMenuWidget->RunBtn , &QToolButton::clicked, this, &MainWindow::_on_clicked_RunBtn);
}
MainWindow::~MainWindow()
{
    delete ui;
}

CodeTreeSideWidget *MainWindow::getCodeTreeSideWidget() const
{
    return codeTreeSideWidget;
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
}

void MainWindow::_on_clicked_CodeBtn()
{
    this->takeCentralWidget();
    this->setCentralWidget(codePageEditWidget);
    this->addDockWidget(Qt::LeftDockWidgetArea, codeTreeSidedockWidget);
    this->addDockWidget(Qt::BottomDockWidgetArea, terminaldockWidget);
    codePageEditWidget->show();
    codeTreeSidedockWidget->show();
    terminaldockWidget->show();
}

void MainWindow::_on_clicked_GenerateBtn()
{
    this->takeCentralWidget();
    this->setCentralWidget(generatePageWidget);
    if(codeTreeSidedockWidget){
        this->removeDockWidget(codeTreeSidedockWidget);
    }
    if(terminaldockWidget != nullptr){
        this->removeDockWidget(terminaldockWidget);
    }
    generatePageWidget->show();
}

void MainWindow::_on_clicked_RunBtn()
{

    QString str("dir\n");
    GlobalData::global_terminalSysteam->sendCommand(str);
}


