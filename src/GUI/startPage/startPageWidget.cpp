#include "startPageWidget.h"
#include "ui_startPageWidget.h"

StartPageWidget::StartPageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartPageWidget)
{
    ui->setupUi(this);
}

StartPageWidget::~StartPageWidget()
{
    delete ui;
}
