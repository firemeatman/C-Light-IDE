#include "genBuildConfigWidget.h"
#include "ui_genBuildConfigWidget.h"

// #include "../../../common/global_data.h"
// #include "../../../common/usefulTool.h"
GenBuildConfigWidget::GenBuildConfigWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GenBuildConfigWidget)
{
    ui->setupUi(this);

    // ui->BuildSysComboBox->addItem("Cmake");
    // ui->BuildSysComboBox->addItem("makefile");
    // ui->BuildSysComboBox->setItemData(0, Project_Type::CMAKE_PROJECT);
    // ui->BuildSysComboBox->setItemData(1, Project_Type::MAKEFILE_PROJECT);

    // ui->cmakeUseBuildComboBox->addItem("Ninja");
    // ui->cmakeUseBuildComboBox->addItem("MSBuild");
    // ui->cmakeUseBuildComboBox->addItem("Make");
    // ui->cmakeUseBuildComboBox->setItemData(0, Buildsystem_Type::Ninja);
    // ui->cmakeUseBuildComboBox->setItemData(1, Buildsystem_Type::MSBuild);
    // ui->cmakeUseBuildComboBox->setItemData(2, Buildsystem_Type::Make);
}

GenBuildConfigWidget::~GenBuildConfigWidget()
{
    delete ui;
}

// void GenBuildConfigWidget::_on_projectLoaded(ProjectConfig *newProject)
// {
//     CMakeSysConfig& cmakeConfig = newProject->cmakeConfig;

//     int num = ui->BuildSysComboBox->count();
//     for(int i=0;i<num;i++){
//         if(ui->BuildSysComboBox->itemData(i).toInt() == newProject->projectType){
//             ui->BuildSysComboBox->setCurrentIndex(i);
//             break;
//         }
//     }
//     ui->cmakeCComplierLineEdit->setText(cmakeConfig.c_ComplierPath);
//     ui->cmakeCXXComplierLineEdit->setText(cmakeConfig.cxx_ComplierPath);
//     ui->cmakePathLineEdit->setText(cmakeConfig.CMakePath);
//     ui->cmakelistFileLineEdit->setText(cmakeConfig.CMakeFilePath);
//     ui->cmakeInstallLineEdit->setText(cmakeConfig.installDir);
//     ui->cmakeUseBuildEdit->setText(cmakeConfig.buildsystemPath);
//     ui->cmakeBuildDirlineEdit->setText(cmakeConfig.buildDir);

//     num = ui->cmakeUseBuildComboBox->count();
//     for(int i=0;i<num;i++){
//         if(ui->cmakeUseBuildComboBox->itemData(i).toInt() == cmakeConfig.buildsystem){
//             ui->cmakeUseBuildComboBox->setCurrentIndex(i);
//             break;
//         }
//     }

// }

void GenBuildConfigWidget::on_BuildSysComboBox_currentIndexChanged(int index)
{
    // ProjectConfig* project = GlobalData::projectSys->getCurrentProject();
    // if(project != nullptr){
    //     project->projectType = (Project_Type)ui->BuildSysComboBox->itemData(index).toInt();
    // }
}


void GenBuildConfigWidget::on_cmakePathBtn_clicked()
{
    // QStringList fileList;
    // QString fileDialogDir;
    // QString name = QStringLiteral("选择cmake程序路径");
    // fileList = UsefulTool::userSelectFile(name, QFileDialog::AnyFile, fileDialogDir, this);
    // if(!fileList.isEmpty()){
    //     QString path = fileList.at(0);
    //     ProjectConfig* project = GlobalData::projectSys->getCurrentProject();
    //     project->cmakeConfig.CMakePath = path;
    //     ui->cmakePathLineEdit->setText(path);
    // }
}


void GenBuildConfigWidget::on_cmakelistFileBtn_clicked()
{
    // QStringList fileList;
    // QString fileDialogDir;
    // QString name = QStringLiteral("选择CMakeLists文件路径");
    // fileList = UsefulTool::userSelectFile(name, QFileDialog::AnyFile, fileDialogDir, this);
    // if(!fileList.isEmpty()){
    //     QString path = fileList.at(0);
    //     ProjectConfig* project = GlobalData::projectSys->getCurrentProject();
    //     project->cmakeConfig.CMakeFilePath = path;
    //     ui->cmakelistFileLineEdit->setText(path);
    // }
}


void GenBuildConfigWidget::on_cmakeCComplierBtn_clicked()
{
    // QStringList fileList;
    // QString fileDialogDir;
    // QString name = QStringLiteral("选择c编译器路径");
    // fileList = UsefulTool::userSelectFile(name, QFileDialog::AnyFile, fileDialogDir, this);
    // if(!fileList.isEmpty()){
    //     QString path = fileList.at(0);
    //     ProjectConfig* project = GlobalData::projectSys->getCurrentProject();
    //     project->cmakeConfig.c_ComplierPath = path;
    //     ui->cmakeCComplierLineEdit->setText(path);
    // }
}


void GenBuildConfigWidget::on_cmakeCXXComplierBtn_clicked()
{
    // QStringList fileList;
    // QString fileDialogDir;
    // QString name = QStringLiteral("选择c++编译器路径");
    // fileList = UsefulTool::userSelectFile(name, QFileDialog::AnyFile, fileDialogDir, this);
    // if(!fileList.isEmpty()){
    //     QString path = fileList.at(0);
    //     ProjectConfig* project = GlobalData::projectSys->getCurrentProject();
    //     project->cmakeConfig.cxx_ComplierPath = path;
    //     ui->cmakeCXXComplierLineEdit->setText(path);
    // }
}


void GenBuildConfigWidget::on_cmakeUseBuildBtn_clicked()
{
    // QStringList fileList;
    // QString fileDialogDir;
    // QString name = QStringLiteral("选择构建系统路径");
    // fileList = UsefulTool::userSelectFile(name, QFileDialog::AnyFile, fileDialogDir, this);
    // if(!fileList.isEmpty()){
    //     QString path = fileList.at(0);
    //     ProjectConfig* project = GlobalData::projectSys->getCurrentProject();
    //     project->cmakeConfig.buildsystemPath = path;
    //     ui->cmakeUseBuildEdit->setText(path);
    // }
}


void GenBuildConfigWidget::on_cmakeBuildDirBtn_clicked()
{
    // QStringList fileList;
    // QString fileDialogDir;
    // QString name = QStringLiteral("选择使用的构建目录");
    // fileList = UsefulTool::userSelectFile(name, QFileDialog::Directory, fileDialogDir, this);
    // if(!fileList.isEmpty()){
    //     QString path = fileList.at(0);
    //     ProjectConfig* project = GlobalData::projectSys->getCurrentProject();
    //     project->cmakeConfig.buildDir = path;
    //     ui->cmakeBuildDirlineEdit->setText(path);
    // }
}


void GenBuildConfigWidget::on_cmakeInstallBtn_clicked()
{
    // QStringList fileList;
    // QString fileDialogDir;
    // QString name = QStringLiteral("选择使用的安装目录");
    // fileList = UsefulTool::userSelectFile(name, QFileDialog::Directory, fileDialogDir, this);
    // if(!fileList.isEmpty()){
    //     QString path = fileList.at(0);
    //     ProjectConfig* project = GlobalData::projectSys->getCurrentProject();
    //     project->cmakeConfig.installDir = path;
    //     ui->cmakeInstallLineEdit->setText(path);
    // }
}

