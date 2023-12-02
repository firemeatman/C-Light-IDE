#include "sideMenuWidget.h"
#include "ui_sideMenuWidget.h"

SideMenuWidget::SideMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideMenuWidget)
{
    ui->setupUi(this);
}

SideMenuWidget::~SideMenuWidget()
{
    delete ui;
}
