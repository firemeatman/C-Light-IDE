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
}

GeneratePageWidget::~GeneratePageWidget()
{
    delete ui;
}

void GeneratePageWidget::_on_clicked_complierSelectBtn()
{

    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选择项目文件夹"));
    fileDialog->setDirectory("C:/");
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        QString filePath = fileNames.at(0);
        ui->label->setText(filePath);
        GlobalData::ComplierPath = filePath;
    }

}

void GeneratePageWidget::_on_clicked_debugerSelectBtn()
{

    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选择项目文件夹"));
    fileDialog->setDirectory("C:/");
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        QString filePath = fileNames.at(0);
        ui->label_2->setText(filePath);
        GlobalData::DebugerPath = filePath;
    }
}

void GeneratePageWidget::_on_clicked_makefileSelectBtn()
{

    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选择项目文件夹"));
    fileDialog->setDirectory("C:/");
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        QString filePath = fileNames.at(0);
        ui->label_3->setText(filePath);
        GlobalData::MakeFilePath = filePath;
    }
}
