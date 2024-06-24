#include "buildConfigerForm.h"
#include "ui_buildConfigerForm.h"

#include "../../../common/global_data.h"

BuildConfigerForm::BuildConfigerForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BuildConfigerForm)
{
    ui->setupUi(this);
}

BuildConfigerForm::~BuildConfigerForm()
{
    delete ui;
}
