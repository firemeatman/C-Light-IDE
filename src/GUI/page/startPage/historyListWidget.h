#ifndef HISTORYLISTWIDGET_H
#define HISTORYLISTWIDGET_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QList>
#include <QMenu>
#include "historyItemForm.h"


class HistoryListWidget : public QListWidget
{
    Q_OBJECT
public:
    HistoryListWidget(QWidget* parent = nullptr);
    ~HistoryListWidget();

    int maxHistoryNum = 10;

    void resetProjectItems(QList<HistoryProject>& list);
    void insetProjectItem(HistoryProject& item, int pos); // pos: 插入位置，-1末尾插入,...
    void deleProjectItem(int index);

private:
    QMenu* menu;

public slots:
    void _on_itemPressed(QListWidgetItem *item);
    void _on_menuTriggered(QAction* act);
};

#endif // HISTORYLISTWIDGET_H
