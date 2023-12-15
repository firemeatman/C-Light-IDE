#ifndef STATUSBARWIDGET_H
#define STATUSBARWIDGET_H

#include <QWidget>

namespace Ui {
class StatusBarWidget;
}

class StatusBarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBarWidget(QWidget *parent = nullptr);
    ~StatusBarWidget();

private:
    Ui::StatusBarWidget *ui;
};

#endif // STATUSBARWIDGET_H
