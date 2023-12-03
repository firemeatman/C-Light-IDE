#include "codePageEditWidget.h"
#include "ui_codePageEditWidget.h"

#include "../commonWidget/codeEditor.h"

CodePageEditWidget::CodePageEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodePageEditWidget)
{
    ui->setupUi(this);
    CodeEditor* codeEditor = new CodeEditor(this);
    codeEditor->resize(500,500);
}

CodePageEditWidget::~CodePageEditWidget()
{
    delete ui;
}
