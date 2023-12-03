
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QToolBar>
#include <QLayout>
#include "sideMenu/sideMenuWidget.h"
#include "startPage/startPageWidget.h"
#include "codePage/codePageEditWidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SideMenuWidget* sideMenuWidget = new SideMenuWidget(this);
    QToolBar* toolBar = new QToolBar(this);
    toolBar->addWidget(sideMenuWidget);
    toolBar->setMovable(false);
    //toolBar->setFixedWidth(50);
    this->addToolBar(Qt::LeftToolBarArea, toolBar);

    //StartPageWidget* startPageWidget = new StartPageWidget(this);
    CodePageEditWidget* codePageEditWidget = new CodePageEditWidget(this);
    this->setCentralWidget(codePageEditWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


