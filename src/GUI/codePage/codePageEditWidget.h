#ifndef CODEPAGEEDITWIDGET_H
#define CODEPAGEEDITWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QByteArray>
#include <QListWidgetItem>
#include "../../codeFileSys/codeFileSys.h"
class QCodeEditor;

namespace Ui {
class CodePageEditWidget;
}

class CodePageEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CodePageEditWidget(QWidget *parent = nullptr);
    ~CodePageEditWidget();

    QCodeEditor* codeEditor;


protected:
    void keyPressEvent(QKeyEvent  *event) override;

private:
    Ui::CodePageEditWidget *ui;
    CodeFileSys::CodeFileInfo* fileInfo = nullptr;

public slots:
    void setTextData(QByteArray& data);
    void writeContentToCache(CodeFileSys::CodeFileInfo* fileInfo);
    void _on_textChanged();

};

#endif // CODEPAGEEDITWIDGET_H
