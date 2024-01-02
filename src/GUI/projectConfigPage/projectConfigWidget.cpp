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

void ProjectConfigWidget::projectLoaded(ProjectConfig *newProject)
{
    if(newProject == nullptr){
        return;
    }
    ui->projectNameLineEdit->setText(newProject->projectName);
    ui->projectRootliLeEdit->setText(newProject->projectRootDir);
    if(newProject->projectType == Project_Type::CMAKE_PROJECT){
        ui->targetNameLabel->setText(newProject->cmakeConfig.targetName);
    }else{
        ui->targetNameLabel->setText(newProject->makeSysConfig.targetName);
    }

}
