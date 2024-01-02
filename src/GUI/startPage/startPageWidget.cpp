#include "startPageWidget.h"
#include "ui_startPageWidget.h"

#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

#include "../codePage/codeTreeSideWidget.h"
#include "../../common/global_data.h"
#include "../../common/usefulTool.h"
#include "../commonWidget/createProjectDialog.h"
StartPageWidget::StartPageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartPageWidget)
{
    ui->setupUi(this);
    connect(ui->openButton, &QPushButton::clicked, this, &StartPageWidget::_on_clicked_openBtn);
    connect(ui->createButton, &QPushButton::clicked, this, &StartPageWidget::_on_clicked_createBtn);
}

StartPageWidget::~StartPageWidget()
{
    delete ui;
}

void StartPageWidget::_on_clicked_openBtn()
{
    QStringList fileList;
    QString fileDialogDir;
    if(!GlobalData::lastProjectDir.isEmpty()){
        fileDialogDir = GlobalData::lastProjectDir;
    }
    QString name = QStringLiteral("选择项目文件夹");
    fileList = UsefulTool::userSelectFile(name, QFileDialog::Directory, fileDialogDir, this);
    if(!fileList.isEmpty()){
        QString path = fileList.at(0);
        GlobalData::lastProjectDir = path;
        // 打开项目
        GlobalData::projectSys->loadProject(path);
        //跳转编码页面
        GlobalData::global_mainWindow->_on_clicked_CodeBtn();
        CodeTreeSideWidget* treeSideWidget = GlobalData::global_mainWindow->getCodeTreeSideWidget();
        treeSideWidget->switchState(CodeTreeSideWidget::OPEN_DIR);
        treeSideWidget->getTreeMenu()->openFileTree(path);
    }

}

void StartPageWidget::_on_clicked_createBtn()
{
    if(createProjectDialog != nullptr){
        return;
    }
    createProjectDialog = new CreateProjectDialog(this);
    connect(createProjectDialog, &CreateProjectDialog::accepted, this, &StartPageWidget::_on_acceptCreate);
    connect(createProjectDialog, &CreateProjectDialog::rejected, this, &StartPageWidget::_on_rejecptCreate);
    createProjectDialog->exec();
}

void StartPageWidget::_on_acceptCreate()
{
    static int count = 0;
    count++;
    qDebug()<<"accept次数："<<count;
    QString errMsg;
    CreateProjectDialog::Back_Params backParams;
    bool flag = true;
    ProjectConfig* project = nullptr;

    createProjectDialog->getBack_Params(&backParams);
    if(backParams.projetName.isEmpty()){
        errMsg = "工程名是空的...";
        goto err_1;
    }
    if(backParams.root.isEmpty()){
        errMsg = "根目录是空的...";
        goto err_1;
    }

    // 创建工程
    flag = GlobalData::projectSys->createProject(backParams.projetName,backParams.root,backParams.type,project);
    if(!flag){
        errMsg = "创建项目配置失败!";
        goto err_1;
    }
    createProjectDialog->close();
    createProjectDialog = nullptr;
    return;

    err_1:
    QMessageBox msgBox;
    msgBox.setText(errMsg);
    msgBox.exec();
}

void StartPageWidget::_on_rejecptCreate()
{
    createProjectDialog->close();
    createProjectDialog = nullptr;
}
