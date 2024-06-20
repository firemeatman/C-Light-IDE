#include "createProjectDialog.h"
#include "ui_createProjectDialog.h"

#include <QDialogButtonBox>
#include <QMessageBox>
#include <QVBoxLayout>

#include "../../../common/global_data.h"
#include "../../../common/usefulTool.h"

CreateProjectDialog::CreateProjectDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateProjectDialog)
{
    ui->setupUi(this);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel, this);
    buttonBox->setCenterButtons(true);
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->addWidget(ui->widget, 4);
    vlayout->addWidget(buttonBox, 1);

    ui->comboBox->addItem("Cmake项目");
    ui->comboBox->addItem("makefile项目");
    ui->comboBox->setItemData(0, "CMake");
    ui->comboBox->setItemData(1, "MakeFile");
    this->setWindowTitle("创建项目");
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setWindowFlags(this->windowFlags()| Qt::Dialog);

    ui->rootLineEdit->setText(GlobalData::lastChoices.createProjectPath);

    connect(ui->rootBtn, &QToolButton::clicked, this, &CreateProjectDialog::_on_clicked_rootBtn);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CreateProjectDialog::_on_acceptCreate);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

}

CreateProjectDialog::~CreateProjectDialog()
{

    GlobalData::lastChoices.createProjectPath = ui->rootLineEdit->text();
    delete ui;
}


void CreateProjectDialog::_on_clicked_rootBtn()
{
    QStringList fileList;
    QString name = QStringLiteral("选择项目根目录");
    fileList = UsefulTool::userSelectFile(name, QFileDialog::Directory, GlobalData::lastChoices.createProjectPath , this);
    if(!fileList.isEmpty()){
        QString name = ui->namelineEdit->text();
        QString path = fileList[0];
        if(!name.isEmpty()){
            path = path + "/" + name;
        }
        ui->rootLineEdit->setText(path);
    }
}

void CreateProjectDialog::_on_acceptCreate()
{
    QString rootPath = ui->rootLineEdit->text();
    QString name = ui->namelineEdit->text();
    QString type = ui->comboBox->currentData().toString();
    QString configFilePath;

    if(name.isEmpty()){
        QMessageBox::warning(this, "创建失败", "项目名不能为空！", QMessageBox::NoButton);
        return;
    }else if(rootPath.isEmpty()){
        QMessageBox::warning(this, "创建失败", "未选择项目根目录！", QMessageBox::NoButton);
        return;
    }
    QDir dir;
    if(!dir.exists(rootPath)){
        dir.mkpath(rootPath);
    }
    configFilePath = rootPath + "/" + name + ".json";

    std::shared_ptr<Project> project = std::make_shared<Project>();
    QJsonObject jRoot = project->getRootConfigJson();
    jRoot.insert(Project::configkey_projectName, name);
    jRoot.insert(Project::configkey_projectType, type);
    project->setRootConfigJson(jRoot);
    project->saveProject(configFilePath);
    GlobalData::projectManager->addProject(project);

    this->accept();
}
