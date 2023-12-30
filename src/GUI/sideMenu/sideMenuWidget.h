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
    QToolButton* ConfigBtn;
    QToolButton* RunBtn;

private:
    Ui::SideMenuWidget *ui;

public slots:
    void _on_clicked_RunBtn();

    void _on_runBtnTaskComplete(QString &taskName, int code, QString &info, QString& from);
};

#endif // SIDEMENUWIDGET_H
