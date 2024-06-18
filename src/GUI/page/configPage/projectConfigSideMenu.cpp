#include "projectConfigSideMenu.h"
#include "ui_projectConfigSideMenu.h"

// #include "../../common/global_data.h"
#include "projectConfigWidget.h"
#include "genBuildConfigWidget.h"
#include "debugConfigWidget.h"

ProjectConfigSideMenu::ProjectConfigSideMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProjectConfigSideMenu)
{
    ui->setupUi(this);

    connect(ui->projectConfigButton, &QPushButton::clicked, this, &ProjectConfigSideMenu::_on_clicked_projectConfigBtn);
    connect(ui->genBuildConfigButton, &QPushButton::clicked, this, &ProjectConfigSideMenu::_on_clicked_genBuildConfigBtn);
    connect(ui->debugConfigButton, &QPushButton::clicked, this, &ProjectConfigSideMenu::_on_clicked_debugConfigBtn);
}

ProjectConfigSideMenu::~ProjectConfigSideMenu()
{
    delete ui;
}

void ProjectConfigSideMenu::_on_clicked_projectConfigBtn()
{
    // MainWindow* mainW = GlobalData::global_mainWindow;
    // ProjectConfigWidget* projectConfigW = mainW->getProjectConfigWidget();
    // mainW->takeCentralWidget();
    // mainW->setCentralWidget(projectConfigW);
    // projectConfigW->show();
}

void ProjectConfigSideMenu::_on_clicked_genBuildConfigBtn()
{
    // MainWindow* mainW = GlobalData::global_mainWindow;
    // GenBuildConfigWidget* genBuildConfigW = mainW->getGenBuildConfigWidget();
    // mainW->takeCentralWidget();
    // mainW->setCentralWidget(genBuildConfigW);
    // genBuildConfigW->show();
}

void ProjectConfigSideMenu::_on_clicked_debugConfigBtn()
{
    // MainWindow* mainW = GlobalData::global_mainWindow;
    // debugConfigWidget* debugConfigW = mainW->getDebugConfigWidget();
    // mainW->takeCentralWidget();
    // mainW->setCentralWidget(debugConfigW);
    // debugConfigW->show();
}
