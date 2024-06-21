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
    fileItemMenu->addAction("关闭");
    fileItemMenu->addAction("关闭其他");
    fileItemMenu->addAction("关闭所有");

    connect(listWidget, &QListWidget::itemPressed, this, &CodeFileListWidget::_on_clickedItem);
    connect(fileItemMenu, &QMenu::triggered, this, &CodeFileListWidget::_on_triggeredMenu);
    connect(listWidget, &QListWidget::currentItemChanged, this, &CodeFileListWidget::_on_currentItemChanged);

    connect(GlobalData::editCodeManager, &EditCodeManager::fileisChangedChanged,this,&CodeFileListWidget::_on_fileisChangedChanged);
    connect(GlobalData::editCodeManager, &EditCodeManager::fileOpened,this,&CodeFileListWidget::_on_fileOpened);
    connect(GlobalData::editCodeManager, &EditCodeManager::fileNameChanged, this, &CodeFileListWidget::_on_fileNameChanged);

}

CodeFileListWidget::~CodeFileListWidget()
{
    listWidget->clear();
    delete ui;
}

int CodeFileListWidget::countRepeatNameNum(QString &name)
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

void CodeFileListWidget::addFileItem(QString &name, QString& filePath)
{
    int repeatNum = countRepeatNameNum(name);
    QString itemName = name + "(" + QString::number(repeatNum) + ")";
    QListWidgetItem* listItem = new QListWidgetItem();
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
            QListWidgetItem* listItem = listWidget->takeItem(i);
            SAFE_DELE_P(listItem);
            break;
        }
    }
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
        addFileItem(file.name, file.path);
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
    if(text == "关闭"){
        QString path = item->toolTip();
        GlobalData::editCodeManager->removeOpenedFile(path);
        QListWidgetItem* p = listWidget->takeItem(listWidget->currentRow());
        SAFE_DELE_P(p);
    }else if(text == "关闭其他"){
        int num = listWidget->count();
        for(int i=num-1; i>=0 ; i--){
            QListWidgetItem* listItem = listWidget->item(i);
            if(listItem != item){
                QString path = listItem->toolTip();
                GlobalData::editCodeManager->removeOpenedFile(path);
                listWidget->takeItem(i);
                SAFE_DELE_P(listItem);
            }
        }
    }else if(text == "关闭所有"){
        int num = listWidget->count();
        for(int i=num-1; i>=0 ; i--){
            QListWidgetItem* listItem = listWidget->item(i);
            QString path = listItem->toolTip();
            GlobalData::editCodeManager->removeOpenedFile(path);
            listWidget->takeItem(i);
            SAFE_DELE_P(listItem);
        }
    }

}



