#include "codePageEditWidget.h"
#include "ui_codePageEditWidget.h"
#include <QGridLayout>
#include <QFile>
#include <QStringDecoder>

#include "../../../common/global_data.h"
CodePageEditWidget::CodePageEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodePageEditWidget)
{
    ui->setupUi(this);

    this->stackedWidget = new QStackedWidget(this);
    QGridLayout* qGridLayout = new QGridLayout(this);
    qGridLayout->addWidget(this->stackedWidget);

    //connect(codeEditor, &QPlainTextEdit::textChanged,this,&CodePageEditWidget::_on_textChanged);
    connect(GlobalData::editCodeManager, &EditCodeManager::fileEditing,this,&CodePageEditWidget::_on_fileEditing);
    connect(GlobalData::editCodeManager, &EditCodeManager::fileOpened,this,&CodePageEditWidget::_on_fileOpened);
    connect(GlobalData::editCodeManager, &EditCodeManager::fileClosed,this,&CodePageEditWidget::_on_fileClosed);
    connect(GlobalData::editCodeManager, &EditCodeManager::fileSave,this,&CodePageEditWidget::_on_fileSave);
}

CodePageEditWidget::~CodePageEditWidget()
{
    delete ui;
}

void CodePageEditWidget::loadEditor(QString &filePath)
{
    if(codeEditorMap.contains(filePath)){
        CodeEditor* codeEditor = codeEditorMap.value(filePath);
        this->stackedWidget->setCurrentWidget(codeEditor);
        currentEdittingFile = filePath;
    }else{
        CodeEditor* codeEditor = new CodeEditor(this);
        codeEditor->setBreakComponent(false);
        codeEditor->setWordWrapMode(QTextOption::NoWrap);

        QFile file(filePath);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            return;
        }
        QByteArray data = file.readAll();
        file.close();
        QString data_str(data);
        codeEditor->setPlainText(data_str);
        QTextDocument* doc = codeEditor->document();
        connect(doc, &QTextDocument::modificationChanged, this, &CodePageEditWidget::_on_modificationChanged);

        codeEditorMap.insert(filePath, codeEditor);
        this->stackedWidget->addWidget(codeEditor);
        if(stackedWidget->count() == 1){
            this->stackedWidget->setCurrentWidget(codeEditor);
        }
        currentEdittingFile = filePath;
    }
}

void CodePageEditWidget::removeEdior(QString &filePath)
{
    if(codeEditorMap.contains(filePath)){
        CodeEditor* codeEditor  = codeEditorMap.value(filePath);
        codeEditorMap.remove(filePath);
        stackedWidget->removeWidget(codeEditor);
        codeEditor->deleteLater();
        currentEdittingFile = "";
    }
}

void CodePageEditWidget::updateEditorData(QString &filePath)
{
    if(codeEditorMap.contains(filePath)){
        CodeEditor* codeEditor  = codeEditorMap.value(filePath);
        QFile file(filePath);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            return;
        }
        QByteArray data = file.readAll();
        QString data_str(data);
        codeEditor->setPlainText(data_str);
        file.close();
    }
}

void CodePageEditWidget::saveEditorData(QString &filePath)
{
    if(codeEditorMap.contains(filePath)){
        CodeEditor* codeEditor  = codeEditorMap.value(filePath);
        QFile file(filePath);
        if(!file.open(QIODevice::WriteOnly)){
            return;
        }
        QString data_str = codeEditor->toPlainText();
        QByteArray data = data_str.toUtf8();
        file.write(data);
        file.close();

        // 重置文档未改变
        codeEditor->document()->setModified(false);
    }
}

void CodePageEditWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_S && event->modifiers() == Qt::CTRL){
        GlobalData::editCodeManager->saveFile(this->currentEdittingFile);
    }
}

void CodePageEditWidget::_on_modificationChanged(bool changed)
{
    GlobalData::editCodeManager->setFileChanged(currentEdittingFile, changed);
}

void CodePageEditWidget::_on_fileEditing(FileStruct file)
{
    loadEditor(file.path);
}

void CodePageEditWidget::_on_fileOpened(FileStruct file)
{
    loadEditor(file.path);
}

void CodePageEditWidget::_on_fileClosed(FileStruct file)
{
    removeEdior(file.path);
}

void CodePageEditWidget::_on_fileSave(FileStruct file)
{
    saveEditorData(file.path);

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



