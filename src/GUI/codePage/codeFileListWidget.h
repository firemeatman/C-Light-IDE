#ifndef CODEFILELISTWIDGET_H
#define CODEFILELISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QByteArray>
#include <QMenu>
class QTreeWidgetItem;

namespace Ui {
class CodeFileListWidget;
}

class CodeFileListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CodeFileListWidget(QWidget *parent = nullptr);
    ~CodeFileListWidget();

    QListWidget* listWidget;

private:
    Ui::CodeFileListWidget *ui;
    QMenu* fileItemMenu = nullptr;

    int countRepeatNum(QString& name);

signals:
    void showFileData(QByteArray& data);
public slots:
    void _on_openFile(QString path,QString name,QTreeWidgetItem *item);
    void _on_doubleClickedItem(QListWidgetItem *item);
    void _on_clickedItem(QListWidgetItem *item);
    void _on_triggeredMenu(QAction* action);
};

#endif // CODEFILELISTWIDGET_H
