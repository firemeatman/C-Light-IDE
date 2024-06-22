#ifndef CODEPAGEEDITWIDGET_H
#define CODEPAGEEDITWIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QStackedWidget>
#include <QMap>
#include "../../../third/CodeEditor/codeEditor/codeEditor.h"
#include "../../../file/editCodeManager.h"
namespace Ui {
class CodePageEditWidget;
}

class CodePageEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CodePageEditWidget(QWidget *parent = nullptr);
    ~CodePageEditWidget();

    QMap<QString, CodeEditor*> codeEditorMap;
    QStackedWidget* stackedWidget;
    QString currentEdittingFile;

    void loadEditor(QString& filePath);
    void removeEdior(QString& filePath);
    void updateEditorData(QString& filePath);
    void saveEditorData(QString& filePath);


protected:
    void keyPressEvent(QKeyEvent  *event) override;

private:
    Ui::CodePageEditWidget *ui;

public slots:
    void _on_modificationChanged(bool changed);
    void _on_fileEditing(FileStruct file);
    void _on_fileOpened(FileStruct file);
    void _on_fileClosed(FileStruct file);
    void _on_fileSave(FileStruct file);


};

#endif // CODEPAGEEDITWIDGET_H
