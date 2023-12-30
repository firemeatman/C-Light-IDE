#include "createProjectDialog.h"
#include "ui_createProjectDialog.h"

CreateProjectDialog::CreateProjectDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateProjectDialog)
{
    ui->setupUi(this);
}

CreateProjectDialog::~CreateProjectDialog()
{
    delete ui;
}
