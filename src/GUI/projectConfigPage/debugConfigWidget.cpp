#include "debugConfigWidget.h"
#include "ui_debugConfigWidget.h"

debugConfigWidget::debugConfigWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::debugConfigWidget)
{
    ui->setupUi(this);
}

debugConfigWidget::~debugConfigWidget()
{
    delete ui;
}
