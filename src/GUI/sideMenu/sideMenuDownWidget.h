#ifndef SIDEMENUDOWNWIDGET_H
#define SIDEMENUDOWNWIDGET_H

#include <QWidget>

namespace Ui {
class SideMenuDownWidget;
}

class SideMenuDownWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SideMenuDownWidget(QWidget *parent = nullptr);
    ~SideMenuDownWidget();

private:
    Ui::SideMenuDownWidget *ui;
};

#endif // SIDEMENUDOWNWIDGET_H
