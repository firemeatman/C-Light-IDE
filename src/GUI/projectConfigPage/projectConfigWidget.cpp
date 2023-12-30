#include "projectConfigWidget.h"
#include "ui_projectConfigWidget.h"

ProjectConfigWidget::ProjectConfigWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProjectConfigWidget)
{
    ui->setupUi(this);
}

ProjectConfigWidget::~ProjectConfigWidget()
{
    delete ui;
}
