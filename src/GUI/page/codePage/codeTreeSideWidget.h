#ifndef CODETREESIDEWIDGET_H
#define CODETREESIDEWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDir>
#include <QMenu>
#include <QLineEdit>
#include "../../../project/project.h"
#include "../../window/actionWindow/createFileDialog.h"

class CodeTreeWidgetItem : public QTreeWidgetItem
{
public:
    explicit CodeTreeWidgetItem(QTreeWidgetItem *parent = nullptr);

    std::shared_ptr<Project> project = nullptr;

};


namespace Ui {
class CodeTreeSideWidget;
}

class CodeTreeSideWidget : public QWidget
{
    Q_OBJECT

public:
    typedef enum{
        ProjectRoot = 0x01,
        File = 0x02,
        Dir = 0x04
    }SelectItemType;


public:
    explicit CodeTreeSideWidget(QWidget *parent = nullptr);
    ~CodeTreeSideWidget();

    void loadProjectFileTree(std::shared_ptr<Project> project);

private:

    CodeTreeWidgetItem* currentEditNameItem = nullptr;

    void loadChildFile(QDir& parentDir, CodeTreeWidgetItem *parent);
    void clearChildren(CodeTreeWidgetItem *parent);
    QString genFileSoleName(QDir& dir, QString name);
    CodeTreeWidgetItem* addChildFileItem(QString& path, CodeTreeWidgetItem *parent);
    void startEditTreeItem(CodeTreeWidgetItem *item, int colum);

public slots:
    void _on_itemDoubleCliced(QTreeWidgetItem *item);
    void _on_itemPressed(QTreeWidgetItem *item, int column);
    void _on_fileMenuTriggered(QAction *action);
    void _on_ProjectAdded(std::shared_ptr<Project> project);
    void _on_ProjectRemoved(std::shared_ptr<Project> project);
    void _on_nameEditingFinished();

private:
    Ui::CodeTreeSideWidget *ui;
    QTreeWidget* treeWidget = nullptr;
    QMenu* fileMenu;
    QMenu* addfileMenu;
    CreateFileDialog* createFileDialog = nullptr;
    //QTreeWidgetItem* rootItem = nullptr;

    QString defaultFileName = "newFile";
    QString defaultDirName = "newFloder";

};

#endif // CODETREESIDEWIDGET_H
