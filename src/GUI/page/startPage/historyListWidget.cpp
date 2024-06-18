#include "historyListWidget.h"
#include <QMessageBox>
#include <QApplication>
#include "../../../common/global_data.h"

HistoryListWidget::HistoryListWidget(QWidget* parent)
    : QListWidget(parent)
{

    this->menu = new QMenu(this);
    menu->addAction("清除该项记录");
    menu->addAction("清除所有历史项目记录");

    resetProjectItems(GlobalData::historyProjectList);
    connect(this, &QListWidget::itemPressed, this, &HistoryListWidget::_on_itemPressed);
    connect(menu, &QMenu::triggered, this, &HistoryListWidget::_on_menuTriggered);
}

HistoryListWidget::~HistoryListWidget()
{
    int size = this->count();
    GlobalData::historyProjectList.clear();
    for(int i=0;i<size;i++){
        HistoryItemForm* form = static_cast<HistoryItemForm*>(this->itemWidget(this->item(i)));
        if(form){
            HistoryProject item = {form->name, form->path};
            GlobalData::historyProjectList.append(item);
        }
    }

    this->clear();
}

void HistoryListWidget::resetProjectItems(QList<HistoryProject> &list)
{
    int old_count = this->count();
    for(int i=old_count-1; i>=0 ;i--){
        deleProjectItem(i);
    }

    int size = list.count();
    size = std::min(size, this->maxHistoryNum);
    for(int i=0;i<size;i++){
        QListWidgetItem* item = new QListWidgetItem();
        HistoryItemForm* form = new HistoryItemForm(this);
        form->resize(this->width(),50);
        item->setSizeHint(form->size());
        form->setData(list[i]);
        this->addItem(item);
        this->setItemWidget(item, form);
    }

}

void HistoryListWidget::insertProjectItem(HistoryProject &item, int pos)
{
    int size = this->count();
    int index = 0;
    if(pos > size) return;
    if(pos < 0) index = size;
    else index = pos;

    QListWidgetItem* listItem = new QListWidgetItem();
    HistoryItemForm* form = new HistoryItemForm(this);
    form->resize(this->width(),50);
    listItem->setSizeHint(form->size());
    form->setData(item);
    this->insertItem(index, listItem);
    this->setItemWidget(listItem, form);

    size = this->count();
    if(size > this->maxHistoryNum){
        deleProjectItem(size - 1);
    }
}

void HistoryListWidget::deleProjectItem(int index)
{
    if(index < 0 || index >= this->count()) return;

    QListWidgetItem* listItem = this->item(index);
    QWidget* form = this->itemWidget(listItem);
    this->takeItem(index);

    form->deleteLater();
    SAFE_DELE_P(listItem);
}

int HistoryListWidget::isProjectItemExist(QString &configPath)
{
    int size = this->count();
    int  index = -1;
    for(int i=0;i<size;i++){
        HistoryItemForm* form = static_cast<HistoryItemForm*>(this->itemWidget(this->item(i)));
        if(!form) continue;
        if(configPath == form->path){
            index = i;
            break;
        }
    }
    return index;
}

void HistoryListWidget::_on_itemPressed(QListWidgetItem *item)
{
    this->setCurrentItem(item);

    if(qApp->mouseButtons() == Qt::RightButton){
        this->menu->exec(QCursor::pos());  //显示右键菜单栏
        return;
    }

    HistoryItemForm* form = static_cast<HistoryItemForm*>(this->itemWidget(item));
    // 打开项目
    if(form){
        if(!GlobalData::projectManager->isProjectExist(form->path)){
            std::shared_ptr<Project> project = std::make_shared<Project>();
            if(!project->configProject(form->path)){
                QMessageBox::critical(this, "打开项目出错", "项目配置失败！", QMessageBox::NoButton);
                return;
            }
            GlobalData::projectManager->addProject(project);
        }

        // 跳转
        QVariantMap param;
        GlobalData::mainWindow->jump(WindowPageRoute::CodePage, param);
    }
}

void HistoryListWidget::_on_menuTriggered(QAction *act)
{
    if(act->text() == "清除该项记录"){
        deleProjectItem(this->currentRow());
    }else if(act->text() == "清除所有历史项目记录"){
        QList<HistoryProject> list;
        resetProjectItems(list);
    }
}
