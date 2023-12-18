#include "generateSideMenu.h"
#include "ui_generateSideMenu.h"

#include "../../common/global_data.h"
#include "makeConfigWidget.h"
#include "debugConfigWidget.h"
GenerateSideMenu::GenerateSideMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GenerateSideMenu)
{
    ui->setupUi(this);

    connect(ui->makeConfigButton, &QPushButton::clicked, this, &GenerateSideMenu::_on_clicked_makeConfBtn);
    connect(ui->debugConfigButton, &QPushButton::clicked, this, &GenerateSideMenu::_on_clicked_debugConfBtn);

}

GenerateSideMenu::~GenerateSideMenu()
{
    delete ui;
}

void GenerateSideMenu::_on_clicked_makeConfBtn()
{
    MakeConfigWidget* makeConfigWidget = GlobalData::global_mainWindow->getMakeConfigWidget();
    GlobalData::global_mainWindow->takeCentralWidget();
    GlobalData::global_mainWindow->setCentralWidget(makeConfigWidget);
    makeConfigWidget->show();
}

void GenerateSideMenu::_on_clicked_debugConfBtn()
{
    DebugConfigWidget* debugConfigWidget = GlobalData::global_mainWindow->getDebugConfigWidget();
    GlobalData::global_mainWindow->takeCentralWidget();
    GlobalData::global_mainWindow->setCentralWidget(debugConfigWidget);
    debugConfigWidget->show();

}
