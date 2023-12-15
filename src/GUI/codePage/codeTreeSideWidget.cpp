#include "codeTreeSideWidget.h"
#include "ui_codeTreeSideWidget.h"

#include <QPushButton>
#include <QFileDialog>

CodeTreeSideWidget::CodeTreeSideWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodeTreeSideWidget)
{
    ui->setupUi(this);
    treeMenu = new TreeMenu(this);
    ui->verticalLayout->addWidget(treeMenu);
    treeMenu->hide();
    connect(ui->pushButton, &QPushButton::clicked, this, &CodeTreeSideWidget::_on_clicked_openDirBtn);

}

CodeTreeSideWidget::~CodeTreeSideWidget()
{
    delete ui;
}

void CodeTreeSideWidget::switchState(CodeSideWidgetState state)
{
    if(state == EMPUTY){
        treeMenu->hide();
        ui->widget->show();

    }else if(state == CodeTreeSideWidget::OPEN_DIR){
        if(treeMenu == nullptr){
            treeMenu = new TreeMenu(this);
        }
        ui->widget->hide();
        treeMenu->show();
    }
}

TreeMenu *CodeTreeSideWidget::getTreeMenu() const
{
    return treeMenu;
}

void CodeTreeSideWidget::_on_clicked_openDirBtn()
{
    if(current_state != CodeTreeSideWidget::OPEN_DIR){

        //定义文件对话框类
        QFileDialog *fileDialog = new QFileDialog(this);
        fileDialog->setWindowTitle(QStringLiteral("选择项目文件夹"));
        fileDialog->setDirectory("D:/c_workstation/projects/vscode-test");
        fileDialog->setFileMode(QFileDialog::Directory);
        fileDialog->setViewMode(QFileDialog::Detail);

        //打开文件目录，跳转编码页面
        QStringList fileNames;
        if (fileDialog->exec()) {
            fileNames = fileDialog->selectedFiles();
            QString path = fileNames.at(0);
            treeMenu->openFileTree(path);
            switchState(CodeTreeSideWidget::OPEN_DIR);
        }
    }

}
