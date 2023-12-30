#include "projectConfigSideMenu.h"
#include "ui_projectConfigSideMenu.h"

ProjectConfigSideMenu::ProjectConfigSideMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProjectConfigSideMenu)
{
    ui->setupUi(this);
}

ProjectConfigSideMenu::~ProjectConfigSideMenu()
{
    delete ui;
}
