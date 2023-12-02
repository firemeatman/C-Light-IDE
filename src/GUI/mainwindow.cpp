
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QToolBar>

#include "sideMenu/sideMenuWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SideMenuWidget* sideMenuWidget = new SideMenuWidget(this);
    QToolBar* toolBar = new QToolBar(this);
    toolBar->addWidget(sideMenuWidget);
    this->addToolBar(Qt::LeftToolBarArea, toolBar);
}

MainWindow::~MainWindow()
{
    delete ui;
}


