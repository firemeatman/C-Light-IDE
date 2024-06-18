#include "startPageWidget.h"
#include "ui_startPageWidget.h"

#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>


#include "../../../common/usefulTool.h"


StartPageWidget::StartPageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartPageWidget)
{
    ui->setupUi(this);
    hisWidget = new HistoryListWidget(this);
    ui->verticalLayout_2->setStretch(0, 1);
    ui->verticalLayout_2->addWidget(hisWidget, 8);


    connect(ui->openButton, &QPushButton::clicked, this, &StartPageWidget::_on_clicked_openBtn);
    connect(ui->createButton, &QPushButton::clicked, this, &StartPageWidget::_on_clicked_createBtn);
    connect(GlobalData::projectManager, &ProjectManager::projectAdded, this, &StartPageWidget::_on_projectAdded);
}

StartPageWidget::~StartPageWidget()
{
    delete ui;
}

void StartPageWidget::_on_clicked_openBtn()
{
    QStringList fileList;
    QString name = QStringLiteral("选择项目");
    fileList = UsefulTool::userSelectFile(name, QFileDialog::AnyFile, GlobalData::lastChoices.openProjectPath);

    if(fileList.isEmpty()){
        return;
    }

    // 打开项目
    QString path = fileList.at(0);
    if(!GlobalData::projectManager->isProjectExist(path)){
        std::shared_ptr<Project> project = std::make_shared<Project>();
        if(!project->configProject(path)){
            QMessageBox::critical(this, "打开项目出错", "项目配置失败！", QMessageBox::NoButton);
            return;
        }
        GlobalData::projectManager->addProject(project);
    }

    // 保存状态
    GlobalData::lastChoices.openProjectPath = path;
}

void StartPageWidget::_on_clicked_createBtn()
{
    CreateProjectDialog* dialog = new CreateProjectDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose,true);
    createDialog = dialog;
    connect(dialog, &QDialog::finished, this, &StartPageWidget::_on_create_finished);
    dialog->open();
}

void StartPageWidget::_on_create_finished(int res)
{
    if(res == QDialog::Accepted){

    }
}

void StartPageWidget::_on_projectAdded(std::shared_ptr<Project> project)
{
    // 历史列表变动
    HistoryProject history;
    QJsonObject jRoot = project->getRootConfigJson();
    history.name = jRoot[Project::configkey_projectName].toString();
    history.rootPath = project->configFilePath;
    int pos = this->hisWidget->isProjectItemExist(history.rootPath);
    if(pos >= 0){
        this->hisWidget->deleProjectItem(pos);
    }
    this->hisWidget->insertProjectItem(history, 0);
    // 跳转
    QVariantMap param;
    GlobalData::mainWindow->jump(WindowPageRoute::CodePage, param);
}
