#ifndef PROJECTCONFIGWIDGET_H
#define PROJECTCONFIGWIDGET_H

#include <QWidget>
#include "../../system/projectConfig.h"
namespace Ui {
class ProjectConfigWidget;
}

class ProjectConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectConfigWidget(QWidget *parent = nullptr);
    ~ProjectConfigWidget();

private:
    Ui::ProjectConfigWidget *ui;

public slots:
    void projectLoaded(ProjectConfig* newProject);
};

#endif // PROJECTCONFIGWIDGET_H
