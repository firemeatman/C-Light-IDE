#include "sideMenuWidget.h"
#include "ui_sideMenuWidget.h"
#include <QStyle>
#include <QFile>
#include <QFileInfo>
#include "../../common/global_data.h"

SideMenuWidget::SideMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideMenuWidget)
{
    ui->setupUi(this);

    QFile qssFile("sideMenuWidget.qss");
    if(qssFile.open(QFile::ReadOnly)){
        this->setStyleSheet(qssFile.readAll());
    }
    qssFile.close();

    ui->widget_3->setFixedHeight(250);


    ui->toolButton->setIcon(QIcon("../resource/play_regular_icon_512px.png"));
    ui->toolButton->setText("开始");
    ui->toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    //ui->toolButton->setIconSize(QSize(256,256));
    StartBtn = ui->toolButton;

    ui->toolButton_2->setIcon(QIcon("../resource/code_icon_512px.png"));
    ui->toolButton_2->setText("代码");
    ui->toolButton_2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    //ui->toolButton->setIconSize(QSize(256,256));
    CodeBtn = ui->toolButton_2;

    ui->toolButton_4->setIcon(QIcon("../resource/complier_settings_icon_512px.png"));
    ui->toolButton_4->setText("编译构建");
    ui->toolButton_4->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_4->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    //ui->toolButton->setIconSize(QSize(256,256));
    GenerateBtn = ui->toolButton_4;

    ui->toolButton_5->setIcon(QIcon("../resource/play_regular_icon_512px.png"));
    ui->toolButton_5->setText("运行");
    ui->toolButton_5->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_5->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->toolButton->setIconSize(QSize(256,256));
    RunBtn = ui->toolButton_5;

    ui->toolButton_6->setIcon(QIcon("../resource/play_regular_icon_512px.png"));
    ui->toolButton_6->setText("调试");
    ui->toolButton_6->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_6->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    //ui->toolButton->setIconSize(QSize(256,256));

    connect(RunBtn , &QToolButton::clicked, this, &SideMenuWidget::_on_clicked_RunBtn);


}

SideMenuWidget::~SideMenuWidget()
{
    delete ui;
}

void SideMenuWidget::_on_clicked_RunBtn()
{
    BlockingQueue<ExternProcessThread::CommendStr>* commendQueue = GlobalData::ExternProcessThread->getCommendQueue();
    ExternProcessThread::CommendStr commendStr;
    QMap<QString, QString> params;
    params.insert("makeExePath", GlobalData::makeExePath);
    params.insert("mkFileDir", GlobalData::mainMakefileDir);
    params.insert("mkFileName", GlobalData::mainMakefileFullName);

    commendStr.commendName = "make";
    commendStr.from ="menuRunBtn";
    commendStr.paramMap = params;
    commendQueue->put(commendStr);

    GlobalData::global_mainWindow->_on_clicked_makeOutBtn();

    RunBtn->setDisabled(true);
}

void SideMenuWidget::_on_runBtnTaskComplete(QString &taskName, int code, QString &info, QString &from)
{
    QString ownName = "menuRunBtn";
    // 属于侧边菜单RUN按钮的任务状态机
    if(from == ownName){
        if(taskName == "make"){
            BlockingQueue<ExternProcessThread::CommendStr>* commendQueue = GlobalData::ExternProcessThread->getCommendQueue();
            ExternProcessThread::CommendStr commendStr;
            QMap<QString, QString> params;
            params.insert("workpath", GlobalData::targetExeDir);
            params.insert("exeName", GlobalData::targetExeName);

            commendStr.commendName = "run target";
            commendStr.from = ownName;
            commendStr.paramMap = params;
            commendQueue->put(commendStr);
        }else if(taskName == "run target"){
            RunBtn->setDisabled(false);
        }

    }
}




