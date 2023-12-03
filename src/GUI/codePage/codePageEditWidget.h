#ifndef CODEPAGEEDITWIDGET_H
#define CODEPAGEEDITWIDGET_H

#include <QWidget>

namespace Ui {
class CodePageEditWidget;
}

class CodePageEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CodePageEditWidget(QWidget *parent = nullptr);
    ~CodePageEditWidget();

private:
    Ui::CodePageEditWidget *ui;
};

#endif // CODEPAGEEDITWIDGET_H
