#include "debugConfigWidget.h"
#include "ui_debugConfigWidget.h"

#include <QFileDialog>
#include "../../common/global_data.h"

DebugConfigWidget::DebugConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebugConfigWidget)
{
    ui->setupUi(this);

    connect(ui->debugBtn, &QPushButton::clicked, this, &DebugConfigWidget::_on_clicked_debugerSelectBtn);

    ui->debugEdit->setText(GlobalData::debugerExePath);
}

DebugConfigWidget::~DebugConfigWidget()
{
    delete ui;
}

void DebugConfigWidget::_on_clicked_debugerSelectBtn()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选择调试器路径"));
    if(!GlobalData::debugerExePath.isEmpty()){
        fileDialog->setDirectory(GlobalData::debugerExePath);
    }

    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setOption(QFileDialog::DontUseNativeDialog);
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        QString filePath = fileNames.at(0);
        ui->debugEdit->setText(filePath);
        GlobalData::debugerExePath = filePath;
    }
}
