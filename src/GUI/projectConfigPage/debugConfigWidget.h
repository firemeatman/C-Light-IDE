#ifndef DEBUGCONFIGWIDGET_H
#define DEBUGCONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class debugConfigWidget;
}

class debugConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit debugConfigWidget(QWidget *parent = nullptr);
    ~debugConfigWidget();

private:
    Ui::debugConfigWidget *ui;
};

#endif // DEBUGCONFIGWIDGET_H
