#include "makeInfoWidget.h"
#include "ui_makeInfoWidget.h"

MakeInfoWidget::MakeInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::makeInfoWidget)
{
    ui->setupUi(this);

    this->plainTextEdit = ui->plainTextEdit;
}

MakeInfoWidget::~MakeInfoWidget()
{
    delete ui;
}

void MakeInfoWidget::addMsg(QString& str)
{
    plainTextEdit->appendPlainText(str);
}
