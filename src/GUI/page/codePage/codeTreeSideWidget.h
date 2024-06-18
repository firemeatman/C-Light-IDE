#ifndef CODETREESIDEWIDGET_H
#define CODETREESIDEWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDir>
#include <QMenu>
#include "../../../project/project.h"

namespace Ui {
class CodeTreeSideWidget;
}

class CodeTreeSideWidget : public QWidget
{
    Q_OBJECT

public:
    typedef enum{
        EMPUTY,
        OPEN_DIR,
    } CodeSideWidgetState;


public:
    explicit CodeTreeSideWidget(QWidget *parent = nullptr);
    ~CodeTreeSideWidget();

    void loadProjectFileTree(Project& project);

private:
    void loadChildFile(QDir& parentDir, QTreeWidgetItem *parent);

public slots:
    void _on_itemDoubleCliced(QTreeWidgetItem *item);
    void _on_itemPressed(QTreeWidgetItem *item, int column);
    void _on_rootMenuTriggered(QAction *action);
    void _on_fileMenuTriggered(QAction *action);
    void _on_ProjectAdded(std::shared_ptr<Project> project);

signals:
    void fileOpend(QString filePath, QString name);

private:
    Ui::CodeTreeSideWidget *ui;
    QTreeWidget* treeWidget = nullptr;
    QMenu* treeRootMenu;
    QMenu* fileMenu;
    QMenu* addfileMenu;
    //QTreeWidgetItem* rootItem = nullptr;

};

#endif // CODETREESIDEWIDGET_H
