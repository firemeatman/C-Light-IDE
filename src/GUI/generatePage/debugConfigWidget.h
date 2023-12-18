#ifndef DEBUGCONFIGWIDGET_H
#define DEBUGCONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class DebugConfigWidget;
}

class DebugConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DebugConfigWidget(QWidget *parent = nullptr);
    ~DebugConfigWidget();

private:
    Ui::DebugConfigWidget *ui;
public slots:
    void _on_clicked_debugerSelectBtn();
};

#endif // DEBUGCONFIGWIDGET_H
