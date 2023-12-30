#ifndef GENBUILDCONFIGWIDGET_H
#define GENBUILDCONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class GenBuildConfigWidget;
}

class GenBuildConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GenBuildConfigWidget(QWidget *parent = nullptr);
    ~GenBuildConfigWidget();

private:
    Ui::GenBuildConfigWidget *ui;
};

#endif // GENBUILDCONFIGWIDGET_H
