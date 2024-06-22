#ifndef CODEFILELISTWIDGET_H
#define CODEFILELISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QByteArray>
#include <QMenu>

#include "../../../file/editCodeManager.h"

class CodeFileListWidgetItem : public QListWidgetItem
{
public:
    explicit CodeFileListWidgetItem(QListWidget *parent = nullptr, int type = Type)
        : QListWidgetItem(parent, type){};

    std::shared_ptr<Project> project = nullptr;

};

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

    void setFileItemIsChanged(bool changed);

private:
    Ui::CodeFileListWidget *ui;
    QMenu* fileItemMenu = nullptr;

    int countRepeatNameNum(QString& name);
    int fileItemIndex(QString& path);
    void addFileItem(QString& name, QString& filePath, std::shared_ptr<Project> project);
    void removeFileItem(QString& filePath);

public slots:
    void _on_ProjectRemoved(std::shared_ptr<Project> project);

    void _on_fileisChangedChanged(FileStruct file);
    void _on_fileOpened(FileStruct file);
    void _on_fileNameChanged(FileStruct file);
    void _on_fileClosed(FileStruct file);

    void _on_clickedItem(QListWidgetItem *item);
    void _on_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void _on_triggeredMenu(QAction* action);
};

#endif // CODEFILELISTWIDGET_H
