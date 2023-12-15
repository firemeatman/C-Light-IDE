#include "statusBarWidget.h"
#include "ui_statusBarWidget.h"

StatusBarWidget::StatusBarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBarWidget)
{
    ui->setupUi(this);
}

StatusBarWidget::~StatusBarWidget()
{
    delete ui;
}
