#include "projectConfigWidget.h"
#include "ui_projectConfigWidget.h"

#include "../../common/global_data.h"
#include "../../common/usefulTool.h"
ProjectConfigWidget::ProjectConfigWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProjectConfigWidget)
{
    ui->setupUi(this);

    ui->projectRootliLeEdit->setReadOnly(true);

    connect(ui->projectNameLineEdit, &QLineEdit::editingFinished, this, &ProjectConfigWidget::_on_projectNameEdited);
    connect(ui->targetNameLineEdit, &QLineEdit::editingFinished, this, &ProjectConfigWidget::_on_targetNameEdited);
    connect(ui->projectRootBtn, &QToolButton::clicked, this, &ProjectConfigWidget::_on_clicked_rootBtn);

}

ProjectConfigWidget::~ProjectConfigWidget()
{
    delete ui;
}

void ProjectConfigWidget::_on_projectLoaded(ProjectConfig *newProject)
{
    if(newProject == nullptr){
        return;
    }
    ui->projectNameLineEdit->setText(newProject->projectName);
    ui->projectRootliLeEdit->setText(newProject->projectRootDir);
    if(newProject->projectType == Project_Type::CMAKE_PROJECT){
        ui->targetNameLineEdit->setText(newProject->cmakeConfig.targetName);
    }else{
        ui->targetNameLineEdit->setText(newProject->makeSysConfig.targetName);
    }

}

void ProjectConfigWidget::_on_projectNameEdited()
{
    QString text = ui->projectNameLineEdit->text();
    ProjectConfig* project = GlobalData::projectSys->getCurrentProject();
    if(project == nullptr){
        return;
    }
    if(text.isEmpty()){
        ui->projectNameLineEdit->setText(project->projectName);
        return;
    }
    project->projectName = text;
}

void ProjectConfigWidget::_on_targetNameEdited()
{
    QString text = ui->targetNameLineEdit->text();
    ProjectConfig* project = GlobalData::projectSys->getCurrentProject();
    if(project == nullptr){
        return;
    }
    if(text.isEmpty()){
        QString lastTargetName = "";
        if(project->projectType == Project_Type::CMAKE_PROJECT){
            lastTargetName= project->cmakeConfig.targetName;
        }else{
            lastTargetName= project->makeSysConfig.targetName;
        }
        ui->targetNameLineEdit->setText(lastTargetName);
        return;
    }

    if(project->projectType == Project_Type::CMAKE_PROJECT){
        project->cmakeConfig.targetName = text;
    }else{
        project->makeSysConfig.targetName = text;
    }
}

void ProjectConfigWidget::_on_clicked_rootBtn()
{
    QStringList fileList;
    QString fileDialogDir;
    QString windowTitle = QStringLiteral("选择根目录");
    // if(!GlobalData::lastProjectDir.isEmpty()){
    //     fileDialogDir = GlobalData::lastProjectDir;
    // }
    fileList = UsefulTool::userSelectFile(windowTitle, QFileDialog::Directory, fileDialogDir, this);
    if(!fileList.isEmpty()){
        QString path = fileList.at(0);
        ProjectConfig* project = GlobalData::projectSys->getCurrentProject();
        if(project == nullptr){
            return;
        }
        ui->projectRootliLeEdit->setText(path);
        project->projectRootDir = path;
    }
}
