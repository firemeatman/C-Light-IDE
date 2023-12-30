#include "genBuildConfigWidget.h"
#include "ui_genBuildConfigWidget.h"

GenBuildConfigWidget::GenBuildConfigWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GenBuildConfigWidget)
{
    ui->setupUi(this);
}

GenBuildConfigWidget::~GenBuildConfigWidget()
{
    delete ui;
}
