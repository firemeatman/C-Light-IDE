#include "codePageEditWidget.h"
#include "ui_codePageEditWidget.h"
#include <QGridLayout>
#include <QFile>
#include <QStringDecoder>

// #include "../../common/global_data.h"
CodePageEditWidget::CodePageEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodePageEditWidget)
{
    ui->setupUi(this);
    QPlainTextEdit* m_codeEditor = new QPlainTextEdit(this);
    m_codeEditor->setPlainText  ("int a = 10;");
    m_codeEditor->setWordWrapMode(QTextOption::NoWrap);
    m_codeEditor->resize(500,500);
    QGridLayout* qGridLayout = new QGridLayout(this);
    qGridLayout->addWidget(m_codeEditor);
    codeEditor = m_codeEditor;

    codeEditor->setWordWrapMode(QTextOption::NoWrap);

    //connect(codeEditor, &QPlainTextEdit::textChanged,this,&CodePageEditWidget::_on_textChanged);

}

CodePageEditWidget::~CodePageEditWidget()
{
    delete ui;
}

void CodePageEditWidget::keyPressEvent(QKeyEvent *event)
{
    // if(event->key() == Qt::Key_S && event->modifiers() == Qt::CTRL){
    //     qDebug()<<"ctrl+S";
    //     saveData(currentFileInfo);
    //     GlobalData::codeFileSys->saveAllFile();
    // }
}

// void CodePageEditWidget::saveData(CodeFileSys::CodeFileInfo *target)
// {
//     if(target != nullptr){
//         QString text = codeEditor->toPlainText();
//         QByteArray data = text.toUtf8();
//         if(data.compare(target->data)){
//             GlobalData::codeFileSys->updateCache(target, data);
//         }
//     }
// }


// void CodePageEditWidget::_on_switchFile(CodeFileSys::CodeFileInfo *prevFileInfo, CodeFileSys::CodeFileInfo *nextFileInfo)
// {
//     // 将上一个文件的内容从编辑器写入缓存
//     saveData(prevFileInfo);

//     // 在编辑器上显示当前文件的内容
//     if(nextFileInfo != nullptr){
//         QStringDecoder toUtf16(QStringDecoder::Utf8);
//         QString unicode_str = toUtf16(nextFileInfo->data);
//         codeEditor->setPlainText(unicode_str);
//         currentFileInfo = nextFileInfo;
//     }else{
//         currentFileInfo = nullptr;
//         codeEditor->setPlainText(QString());
//     }

// }


