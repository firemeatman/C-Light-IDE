#include "codePageEditWidget.h"
#include "ui_codePageEditWidget.h"
#include <QGridLayout>
#include <QFile>

#include "../../third/QCodeEditor/include/internal/QCodeEditor.hpp"
#include "../../third/QCodeEditor/include/internal/QSyntaxStyle.hpp"
#include "../../third/QCodeEditor/include/internal/QCXXHighlighter.hpp"
#include "../../common/global_data.h"
CodePageEditWidget::CodePageEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodePageEditWidget)
{
    ui->setupUi(this);
    QCodeEditor* m_codeEditor = new QCodeEditor(this);
    QCXXHighlighter* cXXHighlighter = new QCXXHighlighter();
    m_codeEditor->setPlainText  ("int a = 10;");
    m_codeEditor->setSyntaxStyle(QSyntaxStyle::defaultStyle());
    m_codeEditor->setCompleter  (nullptr);
    m_codeEditor->setHighlighter(cXXHighlighter);
    m_codeEditor->setWordWrapMode(QTextOption::NoWrap);
    m_codeEditor->resize(500,500);
    QGridLayout* qGridLayout = new QGridLayout(this);
    qGridLayout->addWidget(m_codeEditor);
    codeEditor = m_codeEditor;

    //connect(codeEditor, &QPlainTextEdit::textChanged,this,&CodePageEditWidget::_on_textChanged);

}

CodePageEditWidget::~CodePageEditWidget()
{
    delete ui;
}

void CodePageEditWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_S && event->modifiers() == Qt::CTRL){
        qDebug()<<"ctrl+S";
        GlobalData::codeFileSys->saveAllFile();
    }
}


void CodePageEditWidget::setTextData(QByteArray &data)
{
    QString utf8_str = QString::fromLocal8Bit(data);
    codeEditor->setPlainText(utf8_str);
}

void CodePageEditWidget::writeContentToCache(CodeFileSys::CodeFileInfo *fileInfo)
{
    QString text = codeEditor->toPlainText();
    QByteArray data = text.toUtf8();
    if(data.compare(fileInfo->data)){
        GlobalData::codeFileSys->updateCache(fileInfo, data);
    }
}

void CodePageEditWidget::_on_textChanged()
{
    if(fileInfo == nullptr){
        return;
    }
    QString text = codeEditor->toPlainText();
    QByteArray data = text.toUtf8();
    GlobalData::codeFileSys->updateCache(fileInfo, data);

}


