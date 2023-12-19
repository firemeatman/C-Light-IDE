#include "makeConfigWidget.h"
#include "ui_makeConfigWidget.h"

#include <QFileDialog>
#include "../../common/global_data.h"

MakeConfigWidget::MakeConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MakeConfigWidget)
{
    ui->setupUi(this);
    connect(ui->compilerBtn, &QPushButton::clicked, this, &MakeConfigWidget::_on_clicked_complierSelectBtn);
    connect(ui->makeBtn, &QPushButton::clicked, this, &MakeConfigWidget::_on_clicked_makeExeSelectBtn);
    connect(ui->makefileBtn, &QPushButton::clicked, this, &MakeConfigWidget::_on_clicked_mainMakefileSelectBtn);
    connect(ui->exeBtn, &QPushButton::clicked, this, &MakeConfigWidget::_on_clicked_targetExeDirSelectBtn);
    connect(ui->exeNameBtn, &QPushButton::clicked, this, &MakeConfigWidget::_on_clicked_targetExeNameSelectBtn);

    ui->compilerLineEdit->setText( GlobalData::complierDir);
    ui->makeLineEdit->setText(GlobalData::makeExePath);
    ui->makefieLineEdit->setText(GlobalData::mainMakefilePath);
    ui->exeLineEdit->setText(GlobalData::targetExeDir);
    ui->exeNameLineEdit->setText(GlobalData::targetExeName);
}

MakeConfigWidget::~MakeConfigWidget()
{
    delete ui;
}

void MakeConfigWidget::_on_clicked_complierSelectBtn()
{

    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选择编译器总目录"));
    if(!GlobalData::complierDir.isEmpty()){
        fileDialog->setDirectory(GlobalData::complierDir);
    }
    fileDialog->setOption(QFileDialog::DontUseNativeDialog);
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        QString filePath = fileNames.at(0);
        ui->compilerLineEdit->setText(filePath);
        GlobalData::complierDir = filePath;
    }

}

void MakeConfigWidget::_on_clicked_makeExeSelectBtn()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选择make程序路径"));
    if(!GlobalData::makeExePath.isEmpty()){
        QFileInfo fileInfo(GlobalData::makeExePath);
        fileDialog->setDirectory(fileInfo.path());
    }
    fileDialog->setOption(QFileDialog::DontUseNativeDialog);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        QString filePath = fileNames.at(0);
        ui->makeLineEdit->setText(filePath);
        GlobalData::makeExePath = filePath;
    }
}

void MakeConfigWidget::_on_clicked_mainMakefileSelectBtn()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选择工程make文件路径"));
    if(!GlobalData::mainMakefileDir.isEmpty()){
        fileDialog->setDirectory(GlobalData::mainMakefileDir);
    }
    fileDialog->setOption(QFileDialog::DontUseNativeDialog);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (!fileDialog->exec()) {
        return;
    }
    fileNames = fileDialog->selectedFiles();
    QString filePath = fileNames.at(0);
    ui->makefieLineEdit->setText(filePath);
    GlobalData::mainMakefilePath = filePath;
    QFileInfo fileInfo(filePath);
    GlobalData::mainMakefileDir = fileInfo.path();
    GlobalData::mainMakefileFullName = fileInfo.fileName();
}

void MakeConfigWidget::_on_clicked_targetExeNameSelectBtn()
{

    GlobalData::targetExeName = ui->exeNameLineEdit->text();
}

void MakeConfigWidget::_on_clicked_targetExeDirSelectBtn()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选择程序生成目录"));
    if(!GlobalData::targetExeDir.isEmpty()){
        QFileInfo fileInfo(GlobalData::targetExeDir);
        fileDialog->setDirectory(fileInfo.path());
    }
    fileDialog->setOption(QFileDialog::DontUseNativeDialog);
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        QString filePath = fileNames.at(0);
        ui->exeLineEdit->setText(filePath);
        GlobalData::targetExeDir = filePath;
    }
}


