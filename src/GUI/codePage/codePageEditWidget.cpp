#include "codePageEditWidget.h"
#include "ui_codePageEditWidget.h"
#include <QGridLayout>
//#include "../commonWidget/codeEditor.h"
#include "../../third/QCodeEditor/include/internal/QCodeEditor.hpp"
#include "../../third/QCodeEditor/include/internal/QSyntaxStyle.hpp"
#include "../../third/QCodeEditor/include/internal/QCXXHighlighter.hpp"

CodePageEditWidget::CodePageEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodePageEditWidget)
{
    ui->setupUi(this);
//    CodeEditor* codeEditor = new CodeEditor(this);
//    codeEditor->resize(500,500);
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

}

CodePageEditWidget::~CodePageEditWidget()
{
    delete ui;
}
