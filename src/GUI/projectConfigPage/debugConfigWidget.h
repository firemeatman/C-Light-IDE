#ifndef DEBUGCONFIGWIDGET_H
#define DEBUGCONFIGWIDGET_H

#include <QWidget>
#include "../../system/projectConfig.h"
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
public slots:
    void projectLoaded(ProjectConfig* newProject);
};

#endif // DEBUGCONFIGWIDGET_H
