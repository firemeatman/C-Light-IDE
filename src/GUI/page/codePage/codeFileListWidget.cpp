#include "codeFileListWidget.h"
#include "ui_codeFileListWidget.h"

#include <QVBoxLayout>
#include <QDir>
#include <QFile>
#include <QApplication>
#include "../../../common/global_data.h"

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
    fileItemMenu->addAction("保存");
    fileItemMenu->addAction("保存所有");
    fileItemMenu->addSeparator();
    fileItemMenu->addAction("关闭");
    fileItemMenu->addAction("关闭其他");
    fileItemMenu->addAction("关闭所有");

    connect(listWidget, &QListWidget::itemPressed, this, &CodeFileListWidget::_on_clickedItem);
    connect(fileItemMenu, &QMenu::triggered, this, &CodeFileListWidget::_on_triggeredMenu);
    connect(listWidget, &QListWidget::currentItemChanged, this, &CodeFileListWidget::_on_currentItemChanged);

    connect(GlobalData::projectManager, &ProjectManager::projectRemoved, this, &CodeFileListWidget::_on_ProjectRemoved);
    connect(GlobalData::editCodeManager, &EditCodeManager::fileisChangedChanged,this,&CodeFileListWidget::_on_fileisChangedChanged);
    connect(GlobalData::editCodeManager, &EditCodeManager::fileOpened,this,&CodeFileListWidget::_on_fileOpened);
    connect(GlobalData::editCodeManager, &EditCodeManager::fileClosed,this,&CodeFileListWidget::_on_fileClosed);
    connect(GlobalData::editCodeManager, &EditCodeManager::fileNameChanged, this, &CodeFileListWidget::_on_fileNameChanged);

}

CodeFileListWidget::~CodeFileListWidget()
{
    int num = listWidget->count();
    for(int i=0; i<num ; i++){
        CodeFileListWidgetItem* item = dynamic_cast<CodeFileListWidgetItem*>(listWidget->takeItem(i));
        SAFE_DELE_P(item);
    }

    delete ui;
}

int CodeFileListWidget::countRepeatNameNum(QString &name)
{
    int num = listWidget->count();
    int count = 0;
    for(int i=0; i<num ; i++){
        QString text = listWidget->item(i)->text();
        if(text == name){
            count++;
        }
    }
    return count;
}

int CodeFileListWidget::fileItemIndex(QString &path)
{
    int num = listWidget->count();
    int index = -1;
    for(int i=0; i<num ; i++){
        QString text = listWidget->item(i)->toolTip();
        if(text.compare(path) == 0){
            index=i;
        }
    }
    return index;
}

void CodeFileListWidget::addFileItem(QString &name, QString& filePath, std::shared_ptr<Project> project)
{
    int repeatNum = countRepeatNameNum(name);
    QString itemName = name;
    if(repeatNum > 0){
        itemName = itemName + "(" + QString::number(repeatNum) + ")";
    }
    CodeFileListWidgetItem* listItem = new CodeFileListWidgetItem();
    listItem->project = project;
    listItem->setText(itemName);
    listItem->setToolTip(filePath);
    listItem->setIcon(QIcon(":/icons/resource/icons/file.png"));
    this->listWidget->addItem(listItem);
}

void CodeFileListWidget::removeFileItem(QString &filePath)
{
    int num = listWidget->count();
    for(int i=0; i<num ; i++){
        QString text = listWidget->item(i)->toolTip();
        if(text == filePath){
            CodeFileListWidgetItem* listItem = static_cast<CodeFileListWidgetItem*>(listWidget->takeItem(i));
            SAFE_DELE_P(listItem);
            break;
        }
    }
}

void CodeFileListWidget::_on_ProjectRemoved(std::shared_ptr<Project> project)
{
    disconnect(GlobalData::editCodeManager, &EditCodeManager::fileClosed,this,&CodeFileListWidget::_on_fileClosed);
    int num = listWidget->count();
    QString path;
    CodeFileListWidgetItem* item;
    for(int i=num-1; i>=0 ; i--){
        item = static_cast<CodeFileListWidgetItem*>(listWidget->item(i));
        if(item->project == project){
            path = item->toolTip();
            GlobalData::editCodeManager->removeOpenedFile(path);
            listWidget->takeItem(i);
            SAFE_DELE_P(item);           
        }
    }
    connect(GlobalData::editCodeManager, &EditCodeManager::fileClosed,this,&CodeFileListWidget::_on_fileClosed);
}

void CodeFileListWidget::_on_fileisChangedChanged(FileStruct file)
{
    int index = fileItemIndex(file.path);
    if(index < 0) return;
    QListWidgetItem* item = listWidget->item(index);
    if(file.isChanged){
        item->setText(file.name + "*");
    }else{
        item->setText(file.name);
    }
}

void CodeFileListWidget::_on_fileOpened(FileStruct file)
{
    int index = fileItemIndex(file.path);
    if(index >= 0){
        listWidget->setCurrentRow(index);
    }else{
        addFileItem(file.name, file.path, file.project);
    }
}

void CodeFileListWidget::_on_fileNameChanged(FileStruct file)
{
    int index = fileItemIndex(file.path);
    if(index >= 0){
        QListWidgetItem* item = listWidget->item(index);
        if(file.isChanged){
            item->setText(file.name + "*");
        }else{
            item->setText(file.name);
        }
    }
}

void CodeFileListWidget::_on_fileClosed(FileStruct file)
{
    int num = listWidget->count();
    QString path;
    CodeFileListWidgetItem* listItem;
    for(int i=num-1; i>=0 ; i--){
        listItem = static_cast<CodeFileListWidgetItem*>(listWidget->item(i));
        path = listItem->toolTip();
        if(path == file.path){
            listWidget->takeItem(i);
            SAFE_DELE_P(listItem);
            break;
        }
    }
}


// 单击，右键打开菜单；左键显示文件数据
void CodeFileListWidget::_on_clickedItem(QListWidgetItem *item)
{
    Qt::MouseButtons btns = qApp->mouseButtons();
    if(btns == Qt::RightButton){
        fileItemMenu->exec(QCursor::pos());
    }else if(btns == Qt::LeftButton){
        QString path = item->toolTip();
        GlobalData::editCodeManager->editFile(path);
    }
}

void CodeFileListWidget::_on_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
}

void CodeFileListWidget::_on_triggeredMenu(QAction *action)
{
    QString text = action->text();
    QListWidgetItem* item = listWidget->currentItem();

    if(text == "保存"){
        QString path = item->toolTip();
        GlobalData::editCodeManager->saveFile(path);
    }else if(text == "保存所有"){
        int num = listWidget->count();
        for(int i=0; i<num ; i++){
            QString path = listWidget->item(i)->toolTip();
            GlobalData::editCodeManager->saveFile(path);
        }

    }else if(text == "关闭"){
        disconnect(GlobalData::editCodeManager, &EditCodeManager::fileClosed,this,&CodeFileListWidget::_on_fileClosed);
        QString path = item->toolTip();
        GlobalData::editCodeManager->removeOpenedFile(path);
        CodeFileListWidgetItem* p = static_cast<CodeFileListWidgetItem*>(listWidget->takeItem(listWidget->currentRow()));
        SAFE_DELE_P(p);
        connect(GlobalData::editCodeManager, &EditCodeManager::fileClosed,this,&CodeFileListWidget::_on_fileClosed);
    }else if(text == "关闭其他"){
        disconnect(GlobalData::editCodeManager, &EditCodeManager::fileClosed,this,&CodeFileListWidget::_on_fileClosed);
        int num = listWidget->count();
        QString path;
        CodeFileListWidgetItem* listItem;
        for(int i=num-1; i>=0 ; i--){
            listItem = static_cast<CodeFileListWidgetItem*>(listWidget->item(i));
            if(listItem != item){
                path = listItem->toolTip();
                GlobalData::editCodeManager->removeOpenedFile(path);
                listWidget->takeItem(i);
                SAFE_DELE_P(listItem);
            }
        }
        connect(GlobalData::editCodeManager, &EditCodeManager::fileClosed,this,&CodeFileListWidget::_on_fileClosed);
    }else if(text == "关闭所有"){
        disconnect(GlobalData::editCodeManager, &EditCodeManager::fileClosed,this,&CodeFileListWidget::_on_fileClosed);
        int num = listWidget->count();
        QString path;
        CodeFileListWidgetItem* listItem;
        for(int i=num-1; i>=0 ; i--){
            listItem = static_cast<CodeFileListWidgetItem*>(listWidget->item(i));
            path = listItem->toolTip();
            GlobalData::editCodeManager->removeOpenedFile(path);
            listWidget->takeItem(i);
            SAFE_DELE_P(listItem);
        }
        connect(GlobalData::editCodeManager, &EditCodeManager::fileClosed,this,&CodeFileListWidget::_on_fileClosed);
    }

}



