#include "codeFileListWidget.h"
#include "ui_codeFileListWidget.h"

#include <QVBoxLayout>
#include <QDir>
#include <QFile>
#include <QApplication>

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
}

void CodeFileListWidget::_on_triggeredMenu(QAction *action)
{
    QString text = action->text();
    QListWidgetItem* item = listWidget->currentItem();

}



