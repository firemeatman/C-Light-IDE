#include "makeInfoWidget.h"
#include "ui_makeInfoWidget.h"

MakeInfoWidget::MakeInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::makeInfoWidget)
{
    ui->setupUi(this);

    this->plainTextEdit = ui->plainTextEdit;

    //字体色 背景色 字体大小 设置
    QFont font = plainTextEdit->font();
    font.setFamily("Courier New");
    plainTextEdit->setFont(font);

    NormalTextFormat.setForeground(QBrush(QColor(127, 127, 127)));
    //NormalTextFormat.setUnderlineColor("red");
    //NormalTextFormat.setBackground(QBrush(QColor(55,55,55)));
    NormalTextFormat.setFontPointSize(11);

    SystemTextFormat.setForeground(QBrush(QColor(117, 117, 234)));
    SystemTextFormat.setFontPointSize(11);

    ErrorTextFormat.setForeground(QBrush(QColor(188,1,46)));
    ErrorTextFormat.setFontPointSize(11);
}

MakeInfoWidget::~MakeInfoWidget()
{
    delete ui;
}

void MakeInfoWidget::addStr(QString &str, MsgType type)
{

    switch (type) {
    case SysInfoMsg:
        plainTextEdit->mergeCurrentCharFormat(SystemTextFormat);
        plainTextEdit->appendPlainText(str);

        break;
    case ExternInfoMsg:
        plainTextEdit->mergeCurrentCharFormat(NormalTextFormat);
        plainTextEdit->appendPlainText(str);
        break;
    case SysErrorMsg:
        plainTextEdit->mergeCurrentCharFormat(ErrorTextFormat);
        plainTextEdit->appendPlainText(str);
        break;
    default:
        break;
    }
}

void MakeInfoWidget::addMsg(QString& str)
{
    plainTextEdit->mergeCurrentCharFormat(NormalTextFormat);
    plainTextEdit->appendPlainText(str);
}
