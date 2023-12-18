#include "makeInfoWidget.h"
#include "ui_makeInfoWidget.h"
#include "../../common/global_data.h"

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

    connect(ui->cleanButton, &QToolButton::clicked, this, &MakeInfoWidget::_on_cleanButton_clicked);
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

void MakeInfoWidget::_on_cleanButton_clicked(bool is_checked)
{
    if(!is_checked){
        BlockingQueue<ExternProcessThread::CommendStr>* commendQueue = GlobalData::ExternProcessThread->getCommendQueue();
        ExternProcessThread::CommendStr commendStr;
        QMap<QString, QString> params;
        params.insert("makeExePath", GlobalData::getMakeProgramPath());
        params.insert("mkFilePath", GlobalData::getMakeFilePath());
        commendStr.commendName = "clean";
        commendStr.paramMap = params;
        commendQueue->put(commendStr);
    }
}

void MakeInfoWidget::_on_makeCompleted(QString &taskName, int code, QString &info, QString& from)
{
    QString outInfo;
    MakeInfoWidget::MsgType type = SysInfoMsg;
    if(taskName == "make"){
        if(code == 0){
            outInfo = "make完成!";
        }else{
            type = SysErrorMsg;
            outInfo = "make程序异常退出，make失败!";
        }
    }else if(taskName == "clean"){
        if(code == 0){
            outInfo = "clean完成!";
        }else{
            type = SysErrorMsg;
            outInfo = "make程序异常退出，clean失败!";
        }
    }
    addStr(outInfo,type);
}

void MakeInfoWidget::_on_makeStart(QString &taskName, QString &from)
{
    QString outInfo;
    if(taskName == "make"){
        outInfo = "开始make...";
    }else if(taskName == "clean"){
        outInfo = "开始clean...";
    }
    addStr(outInfo,SysInfoMsg);
}

