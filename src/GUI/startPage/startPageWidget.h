#ifndef STARTPAGEWIDGET_H
#define STARTPAGEWIDGET_H

#include <QWidget>

namespace Ui {
class StartPageWidget;
}

class StartPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartPageWidget(QWidget *parent = nullptr);
    ~StartPageWidget();

private:
    Ui::StartPageWidget *ui;

public slots:
    void _on_clicked_openBtn();
};

#endif // STARTPAGEWIDGET_H
