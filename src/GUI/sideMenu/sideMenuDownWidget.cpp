#include "sideMenuDownWidget.h"
#include "ui_sideMenuDownWidget.h"

SideMenuDownWidget::SideMenuDownWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideMenuDownWidget)
{
    ui->setupUi(this);
}

SideMenuDownWidget::~SideMenuDownWidget()
{
    delete ui;
}
