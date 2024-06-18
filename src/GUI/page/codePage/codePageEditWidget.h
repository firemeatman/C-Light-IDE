#ifndef CODEPAGEEDITWIDGET_H
#define CODEPAGEEDITWIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QTreeWidget>
#include <QByteArray>
#include <QListWidgetItem>


namespace Ui {
class CodePageEditWidget;
}

class CodePageEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CodePageEditWidget(QWidget *parent = nullptr);
    ~CodePageEditWidget();

    QPlainTextEdit* codeEditor;



protected:
    void keyPressEvent(QKeyEvent  *event) override;


private:
    Ui::CodePageEditWidget *ui;


};

#endif // CODEPAGEEDITWIDGET_H
