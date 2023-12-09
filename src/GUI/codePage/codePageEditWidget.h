#ifndef CODEPAGEEDITWIDGET_H
#define CODEPAGEEDITWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QByteArray>

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

private:
    Ui::CodePageEditWidget *ui;

public slots:
    void setTextData(QByteArray& data);
};

#endif // CODEPAGEEDITWIDGET_H
