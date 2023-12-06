#ifndef SIDEMENUWIDGET_H
#define SIDEMENUWIDGET_H

#include <QWidget>
#include <QToolButton>
namespace Ui {
class SideMenuWidget;
}

class SideMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SideMenuWidget(QWidget *parent = nullptr);
    ~SideMenuWidget();

    QToolButton* StartBtn;
    QToolButton* CodeBtn;
    QToolButton* GenerateBtn;
    QToolButton* RunBtn;

private:
    Ui::SideMenuWidget *ui;


};

#endif // SIDEMENUWIDGET_H
