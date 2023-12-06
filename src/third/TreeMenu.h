
#ifndef __TREEMENU_H
#define __TREEMENU_H

#include <QTreeWidget>
#include <QDir>

#include "newBuildfolder.h"
#include "newBulidFile.h"

// 显示文件树的窗体
class TreeMenu : public QTreeWidget{
    Q_OBJECT
public:
    TreeMenu(QWidget *parent = 0);
    ~TreeMenu();
    void openFileTree(QString path);
    void CreateTopItem(QString path);
    void FindFile(QDir *path,QTreeWidgetItem *parent);
    void buttonCollapseItem();
private:
    QTreeWidgetItem *root = nullptr; //树的根
    QMenu *dirMenu = nullptr;  //文件夹菜单栏
    QMenu *fileMenu = nullptr;  //文件菜单栏
    QTreeWidgetItem *nowItem = nullptr; //当前光标所在Item
    int nowCol; //当前所在列
    NewBulidFile *newFileWidget = nullptr;
    NewBuildfolder *newDirWidget = nullptr;
signals:
    void openFileSignal(QString path,QString name,QTreeWidgetItem *item);
    void collapseItemSignal(const QTreeWidgetItem *item);
    void renameSignal();
private slots:
    void DoubleClickpath(QTreeWidgetItem *item, int column);
    void itemPressedSlot(QTreeWidgetItem * pressedItem, int column);
    void tempActionInformation(QAction *act);
    void bulidNewFileSlot(bool flag);
    void closeBuildFileSlot(bool flag);
    void buildNewDirSlot(bool flag);
    void cancelDirSlot(bool flag);
};

#endif

