#include "sideMenuWidget.h"
#include "ui_sideMenuWidget.h"
#include <QStyle>
SideMenuWidget::SideMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideMenuWidget)
{
    ui->setupUi(this);

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
    ui->toolButton_5->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    ui->toolButton->setIconSize(QSize(256,256));
    RunBtn = ui->toolButton_5;

    ui->toolButton_6->setIcon(QIcon("../resource/play_regular_icon_512px.png"));
    ui->toolButton_6->setText("调试");
    ui->toolButton_6->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_6->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    //ui->toolButton->setIconSize(QSize(256,256));


}

SideMenuWidget::~SideMenuWidget()
{
    delete ui;
}




