#include "historyItemForm.h"
#include "ui_historyItemForm.h"

HistoryItemForm::HistoryItemForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HistoryItemForm)
{
    ui->setupUi(this);
}

HistoryItemForm::~HistoryItemForm()
{
    delete ui;
}

void HistoryItemForm::setData(HistoryProject &data)
{
    this->name = data.name;
    this->path = data.rootPath;
    ui->nameLabel->setText(data.name);
    ui->pathLabel->setText(data.rootPath);
}
