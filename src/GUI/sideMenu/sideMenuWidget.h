#ifndef SIDEMENUWIDGET_H
#define SIDEMENUWIDGET_H

#include <QWidget>

namespace Ui {
class SideMenuWidget;
}

class SideMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SideMenuWidget(QWidget *parent = nullptr);
    ~SideMenuWidget();

private:
    Ui::SideMenuWidget *ui;
};

#endif // SIDEMENUWIDGET_H
