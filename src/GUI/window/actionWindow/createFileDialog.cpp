#include "createFileDialog.h"
#include "ui_createFileDialog.h"

#include <QMessageBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
//#include "../../../common/global_data.h"
#include "../../../common/usefulTool.h"

CreateFileDialog::CreateFileDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateFileDialog)
{
    ui->setupUi(this);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                           | QDialogButtonBox::Cancel, this);
    buttonBox->setCenterButtons(true);
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->addWidget(ui->widget);
    vlayout->addWidget(buttonBox);

    connect(ui->filleBtn, &QToolButton::clicked, this, &CreateFileDialog::_on_fileClicked);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CreateFileDialog::_on_accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::rejected);
}

CreateFileDialog::~CreateFileDialog()
{
    delete ui;
}

void CreateFileDialog::_on_fileClicked()
{
    QStringList fileList;
    QString name = QStringLiteral("选择文件创建目录");
    fileList = UsefulTool::userSelectFile(name, QFileDialog::Directory, this->defalutDir , this);
    if(!fileList.isEmpty()){
        QString name = ui->nameEdit->text();
        QString path = fileList[0];
        if(!name.isEmpty()){
            path = path + "/" + name;
        }
        ui->pathEdit->setText(path);
    }
}

void CreateFileDialog::_on_accept()
{
    QString rootPath = ui->pathEdit->text();
    QString name = ui->nameEdit->text();
    QString configFilePath;

    if(name.isEmpty()){
        QMessageBox::warning(this, "创建失败", "文件名不能为空！", QMessageBox::NoButton);
        return;
    }else if(rootPath.isEmpty()){
        QMessageBox::warning(this, "创建失败", "未选择创建路径！", QMessageBox::NoButton);
        return;
    }
    QDir dir;
    if(!dir.exists(rootPath)){
        dir.mkpath(rootPath);
    }
    QFile file(rootPath);
    if (!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(this, "创建失败", "无法创建该文件！", QMessageBox::NoButton);
        return;
    }
    file.close();

    this->accept();
}
