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

    ui->toolButton_2->setIcon(QIcon("../resource/code_icon_512px.png"));
    ui->toolButton_2->setText("代码");
    ui->toolButton_2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    ui->toolButton_3->setIcon(QIcon("../resource/document_icon_512px.png"));
    ui->toolButton_3->setText("构建文件");
    ui->toolButton_3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_3->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    ui->toolButton_4->setIcon(QIcon("../resource/complier_settings_icon_512px.png"));
    ui->toolButton_4->setText("编译器");
    ui->toolButton_4->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_4->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);


    ui->toolButton_5->setIcon(QIcon("../resource/play_regular_icon_512px.png"));
    ui->toolButton_5->setText("运行");
    ui->toolButton_5->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_5->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);


    ui->toolButton_6->setIcon(QIcon("../resource/play_regular_icon_512px.png"));
    ui->toolButton_6->setText("调试");
    ui->toolButton_6->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButton_6->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
}

SideMenuWidget::~SideMenuWidget()
{
    delete ui;
}
