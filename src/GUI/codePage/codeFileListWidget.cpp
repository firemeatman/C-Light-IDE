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

    // 打开的文件列表
    listWidget = new QListWidget(this);
    listWidget->setObjectName("fileListWidget");
    listWidget->setStyleSheet("#fileListWidget::item:selected { \
                    background-color: #74787a; \
                    } \
                    #fileListWidget::item:hover { \
                            background-color: #cdd1d3; \
                     }   \
                              ");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(listWidget);

    // 文件右键菜单
    fileItemMenu = new QMenu(this);
    fileItemMenu->addAction("关闭");
    fileItemMenu->addAction("关闭其他");
    fileItemMenu->addAction("关闭所有");

    connect(listWidget, &QListWidget::itemPressed, this, &CodeFileListWidget::_on_clickedItem);
    connect(fileItemMenu, &QMenu::triggered, this, &CodeFileListWidget::_on_triggeredMenu);
    connect(listWidget, &QListWidget::currentItemChanged, this, &CodeFileListWidget::_on_currentItemChanged);

}

CodeFileListWidget::~CodeFileListWidget()
{
    delete ui;
}

int CodeFileListWidget::countRepeatNum(QString &name)
{
    int num = listWidget->count();
    int count = 0;
    for(int i=0; i<num ; i++){
        QString text = listWidget->item(i)->text();
        if(text.compare(name) == 0){
            count++;
        }
    }
    return count;
}


void CodeFileListWidget::_on_openFile(QString path, QString name, QTreeWidgetItem *item)
{
    QString itemName = name;
    CodeFileSys::CodeFileInfo* targetCodeFile = nullptr;
    // 根据item查找file数据
    for(CodeFileSys::CodeFileInfo* v : GlobalData::codeFileSys->opendCodeFileList){
        if(path.compare(v->path) == 0){
            targetCodeFile = v;
        }
    }
    // 打开文件并添加进列表，或者之间跳转。
    if(targetCodeFile == nullptr){
        CodeFileSys::CodeFileInfo* fileInfo = new CodeFileSys::CodeFileInfo();
        QFile file(path);
        bool isOk = file.open(QIODevice::ReadWrite);
        if(isOk){
            fileInfo->path = path;
            fileInfo->data =  file.readAll();
            fileInfo->realName = name;
            int reapeatNum = countRepeatNum(name);
            if(reapeatNum > 0){
                itemName.append("(").append(QString::number(reapeatNum)).append(")");
            }
            fileInfo->itemName = itemName;
            fileInfo->item = new QListWidgetItem(itemName);
            listWidget->addItem(fileInfo->item);
            GlobalData::codeFileSys->opendCodeFileList.append(fileInfo);
        }
        file.close();
        listWidget->setCurrentItem(fileInfo->item);
        //emit showFileData(fileInfo->data);
    }else{
        listWidget->setCurrentItem(targetCodeFile->item);
        //emit showFileData(targetCodeFile->data);
    }

}

// 单击，右键打开菜单；左键显示文件数据
void CodeFileListWidget::_on_clickedItem(QListWidgetItem *item)
{
    if(qApp->mouseButtons() == Qt::RightButton){
        fileItemMenu->exec(QCursor::pos());
    }
}

void CodeFileListWidget::_on_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    CodeFileSys::CodeFileInfo* currentFileInfo = nullptr;
    CodeFileSys::CodeFileInfo* prevFileInfo = nullptr;
    int count = 0;
    for(CodeFileSys::CodeFileInfo* v : GlobalData::codeFileSys->opendCodeFileList){
        if(count >= 2){
            break;
        }
        if(v->item == previous){
            prevFileInfo = v;
            count++;
        }else if(v->item == current){
            currentFileInfo = v;
            count++;
        }
    }
    emit switchFile(prevFileInfo, currentFileInfo);
}

void CodeFileListWidget::_on_triggeredMenu(QAction *action)
{
    QString text = action->text();
    QListWidgetItem* item = listWidget->currentItem();

    int size = GlobalData::codeFileSys->opendCodeFileList.size();
    int index = -1;
    CodeFileSys::CodeFileInfo* fileInfo = nullptr;
    CodeFileSys::CodeFileInfo* nearFileInfo = nullptr;

    if(text.compare("关闭") == 0){
        // 找到目标的fileinfo，并找到相邻的。
        for(int i=0;i<size;i++){
            if((GlobalData::codeFileSys->opendCodeFileList[i])->item == item){
                index = i;
                fileInfo = GlobalData::codeFileSys->opendCodeFileList[i];
                if(i>0){
                    nearFileInfo = GlobalData::codeFileSys->opendCodeFileList[i-1];
                }else if(size > 1) {
                    nearFileInfo = GlobalData::codeFileSys->opendCodeFileList[i+1];
                }
            }
        }
        // 删除目标，设置相邻的文件进行显示
        if(index >= 0){
            GlobalData::codeFileSys->opendCodeFileList.remove(index);
            delete fileInfo;
            fileInfo = nullptr;
            listWidget->removeItemWidget(item);
            delete item;
            item = nullptr;
            if(nearFileInfo != nullptr){
                listWidget->setCurrentItem(nearFileInfo->item);
                // emit showFileData(nearFileInfo->data);
            }else{
                // QByteArray array;
                // emit showFileData(array);
                emit switchFile(nullptr, nullptr);
            }
        }
    }else if(text.compare("关闭其他") == 0){
        for(int i=0 ;i < size; i++){
            if((GlobalData::codeFileSys->opendCodeFileList[i])->item != item){

                listWidget->removeItemWidget(GlobalData::codeFileSys->opendCodeFileList[i]->item);
                delete GlobalData::codeFileSys->opendCodeFileList[i]->item;
                GlobalData::codeFileSys->opendCodeFileList[i]->item = nullptr;

                delete GlobalData::codeFileSys->opendCodeFileList[i];
                GlobalData::codeFileSys->opendCodeFileList[i] = nullptr;
                GlobalData::codeFileSys->opendCodeFileList.removeAt(i);

                size = GlobalData::codeFileSys->opendCodeFileList.size();
                i--;
            }else{
                fileInfo = GlobalData::codeFileSys->opendCodeFileList[i];
            }
        }
        listWidget->setCurrentItem(item);
        if(fileInfo != nullptr) emit switchFile(nullptr, fileInfo);

    }else if(text.compare("关闭所有") == 0){
        qDeleteAll(GlobalData::codeFileSys->opendCodeFileList);
        GlobalData::codeFileSys->opendCodeFileList.clear();
        listWidget->clear();
        QByteArray array;
        emit switchFile(nullptr, nullptr);
    }
}



