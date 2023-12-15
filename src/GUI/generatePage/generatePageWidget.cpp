#include "generatePageWidget.h"
#include "ui_generatePageWidget.h"

#include <QFileDialog>
#include "../../common/global_data.h"
GeneratePageWidget::GeneratePageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneratePageWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &GeneratePageWidget::_on_clicked_complierSelectBtn);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &GeneratePageWidget::_on_clicked_debugerSelectBtn);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &GeneratePageWidget::_on_clicked_makefileSelectBtn);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &GeneratePageWidget::_on_clicked_makeSelectBtn);

    ui->lineEdit->setText( GlobalData::ComplierPath);
    ui->lineEdit_4->setText(GlobalData::getMakeProgramPath());
    ui->lineEdit_2->setText(GlobalData::getDebugerPath());
    ui->lineEdit_3->setText(GlobalData::getMakeFilePath());

}

GeneratePageWidget::~GeneratePageWidget()
{
    delete ui;
}

void GeneratePageWidget::_on_clicked_complierSelectBtn()
{

    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选择编译器路径"));
    fileDialog->setDirectory("D:/c_workstation/compiler/TDM-GCC-64/bin");
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        QString filePath = fileNames.at(0);
        ui->lineEdit->setText(filePath);
        GlobalData::ComplierPath = filePath;
    }

}

void GeneratePageWidget::_on_clicked_makeSelectBtn()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选择make程序路径"));
    fileDialog->setDirectory("D:/c_workstation/compiler/TDM-GCC-64/bin");
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        QString filePath = fileNames.at(0);
        ui->lineEdit_4->setText(filePath);
        GlobalData::setMakeProgramPath(filePath);
    }
}

void GeneratePageWidget::_on_clicked_debugerSelectBtn()
{

    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选择调试器路径"));
    fileDialog->setDirectory("D:/c_workstation/compiler/TDM-GCC-64/bin");
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        QString filePath = fileNames.at(0);
        ui->lineEdit_2->setText(filePath);
        GlobalData::setDebugerPath(filePath);
    }
}

void GeneratePageWidget::_on_clicked_makefileSelectBtn()
{

    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选择makefile文件所在文件夹"));
    fileDialog->setDirectory("D:/c_workstation/projects/vscode-test");
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        QString filePath = fileNames.at(0);
        ui->lineEdit_3->setText(filePath);
        GlobalData::setMakeFilePath(filePath);
    }
}
