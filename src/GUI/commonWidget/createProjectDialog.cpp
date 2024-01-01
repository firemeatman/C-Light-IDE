#include "createProjectDialog.h"
#include "ui_createProjectDialog.h"

#include "../../common/usefulTool.h"

CreateProjectDialog::CreateProjectDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateProjectDialog)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Cmake项目");
    ui->comboBox->addItem("makefile项目");
    ui->comboBox->setItemData(0, Project_Type::CMAKE_PROJECT);
    ui->comboBox->setItemData(1, Project_Type::MAKEFILE_PROJECT);

    this->setWindowTitle("创建项目");
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setWindowFlags(this->windowFlags()| Qt::Dialog);
    connect(ui->rootBtn, &QToolButton::clicked, this, &CreateProjectDialog::_on_clicked_rootBtn);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CreateProjectDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &CreateProjectDialog::reject);

}

CreateProjectDialog::~CreateProjectDialog()
{
    delete ui;
}

void CreateProjectDialog::getBack_Params(Back_Params* data)
{
    data->projetName = ui->namelineEdit->text();
    data->root = ui->rootLineEdit->text();
    data->type = (Project_Type)(ui->comboBox->currentData().toInt());
}

void CreateProjectDialog::_on_clicked_rootBtn()
{
    QStringList fileList;
    QString path = QStringLiteral("");
    QString name = QStringLiteral("选择项目根目录");
    fileList = UsefulTool::userSelectFile(name, QFileDialog::Directory, path , this);
    if(!fileList.isEmpty()){
        ui->rootLineEdit->setText(fileList[0]);
    }
}
