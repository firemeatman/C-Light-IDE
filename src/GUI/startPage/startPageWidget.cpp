#include "startPageWidget.h"
#include "ui_startPageWidget.h"

#include <QPushButton>
#include <QFileDialog>

#include "../codePage/codeTreeSideWidget.h"
#include "../../common/global_data.h"

StartPageWidget::StartPageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartPageWidget)
{
    ui->setupUi(this);
    connect(ui->openButton, &QPushButton::clicked, this, &StartPageWidget::_on_clicked_openBtn);
}

StartPageWidget::~StartPageWidget()
{
    delete ui;
}

void StartPageWidget::_on_clicked_openBtn()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选择项目文件夹"));
    fileDialog->setDirectory("C:/");
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setViewMode(QFileDialog::Detail);

    //打开文件目录，跳转编码页面
    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        QString path = fileNames.at(0);
        GlobalData::global_mainWindow->_on_clicked_CodeBtn();
        CodeTreeSideWidget* treeSideWidget = GlobalData::global_mainWindow->getCodeTreeSideWidget();
        treeSideWidget->switchState(CodeTreeSideWidget::OPEN_DIR);
        treeSideWidget->getTreeMenu()->openFileTree(path);
    }
}
