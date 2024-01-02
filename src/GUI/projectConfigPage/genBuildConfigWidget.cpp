#include "genBuildConfigWidget.h"
#include "ui_genBuildConfigWidget.h"

GenBuildConfigWidget::GenBuildConfigWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GenBuildConfigWidget)
{
    ui->setupUi(this);

    ui->cmakeUseBuildComboBox->addItem("Ninja");
    ui->cmakeUseBuildComboBox->addItem("MSBuild");
    ui->cmakeUseBuildComboBox->addItem("Make");
    ui->cmakeUseBuildComboBox->setItemData(0, Buildsystem_Type::Ninja);
    ui->cmakeUseBuildComboBox->setItemData(1, Buildsystem_Type::MSBuild);
    ui->cmakeUseBuildComboBox->setItemData(2, Buildsystem_Type::Make);
}

GenBuildConfigWidget::~GenBuildConfigWidget()
{
    delete ui;
}

void GenBuildConfigWidget::projectLoaded(ProjectConfig *newProject)
{
    CMakeSysConfig& cmakeConfig = newProject->cmakeConfig;
    ui->cmakeCComplierLineEdit->setText(cmakeConfig.c_ComplierPath);
    ui->cmakeCXXComplierLineEdit->setText(cmakeConfig.cxx_ComplierPath);
    ui->cmakePathLineEdit->setText(cmakeConfig.CMakePath);
    ui->cmakelistFileLineEdit->setText(cmakeConfig.CMakeFilePath);
    ui->cmakeInstallLineEdit->setText(cmakeConfig.installDir);
    ui->cmakeUseBuildEdit->setText(cmakeConfig.buildsystemPath);
    ui->cmakeBuildDirlineEdit->setText(cmakeConfig.buildDir);

    int num = ui->cmakeUseBuildComboBox->count();
    for(int i=0;i<num;i++){
        if(ui->cmakeUseBuildComboBox->itemData(i).toInt() == cmakeConfig.buildsystem){
            ui->cmakeUseBuildComboBox->setCurrentIndex(i);
            break;
        }
    }

}
