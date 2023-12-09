#include "codeFileListWidget.h"
#include "ui_codeFileListWidget.h"

#include <QVBoxLayout>
#include <QDir>
#include <QFile>
#include "../../common/global_data.h"


CodeFileListWidget::CodeFileListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodeFileListWidget)
{
    ui->setupUi(this);

    listWidget = new QListWidget(this);
    listWidget->setObjectName("fileListWidget");
    listWidget->setStyleSheet("#fileListWidget::item:selected { \
                    background-color: #777777; \
                    } \
                    #fileListWidget::item:hover { \
                            background-color: #f5f5f5; \
                     }   \
                              ");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(listWidget);

    connect(listWidget, &QListWidget::itemDoubleClicked, this, &CodeFileListWidget::_on_doubleClickedItem);
}

CodeFileListWidget::~CodeFileListWidget()
{
    delete ui;
}

bool CodeFileListWidget::nameIsRepeat(QString &name)
{
    int num = listWidget->count();
    for(int i=0; i<num ; i++){
        QString text = listWidget->item(num)->text();
        if(text.compare(name) == 0){
            return true;
        }
    }
    return false;
}

void CodeFileListWidget::_on_openFile(QString path, QString name, QTreeWidgetItem *item)
{
    QString itemName = name;
    if(!GlobalData::codeFileSys->findFile(path)){
        CodeFileSys::FileInfo* fileInfo = new CodeFileSys::FileInfo();
        QFile file(path);
        bool isOk = file.open(QIODevice::ReadWrite);
        if(isOk){
            fileInfo->data =  file.readAll();
            fileInfo->name = name;
            if(nameIsRepeat(name)){
                itemName.append("_1");
            }
            fileInfo->item = new QListWidgetItem(itemName);
            listWidget->addItem(fileInfo->item);
            GlobalData::codeFileSys->addFileInfo(path, fileInfo);
        }
        file.close();
    }else{
        CodeFileSys::FileInfo* fileInfo = GlobalData::codeFileSys->findFile(path);
        _on_doubleClickedItem(fileInfo->item);
    }

}

void CodeFileListWidget::_on_doubleClickedItem(QListWidgetItem *item)
{
    CodeFileSys::FileInfo* fileInfo = GlobalData::codeFileSys->findFile(item);
    emit showFileData(fileInfo->data);

}


