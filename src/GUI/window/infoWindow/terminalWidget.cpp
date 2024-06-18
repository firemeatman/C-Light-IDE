
#include "terminalWidget.h"

#include <QVBoxLayout>


TerminalWidget::TerminalWidget(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* vBoxLayout =new QVBoxLayout(this);
    plainTextEdit = new QPlainTextEdit(this);
    vBoxLayout->addWidget(plainTextEdit);

}

TerminalWidget::~TerminalWidget()
{

}

void TerminalWidget::addMsg(QString &str)
{

    plainTextEdit->appendPlainText(str);
}

void TerminalWidget::setMsg(QString &str)
{
    plainTextEdit->setPlainText(str);
}

void TerminalWidget::clearMsg(QString &str)
{
    plainTextEdit->clear();
}

