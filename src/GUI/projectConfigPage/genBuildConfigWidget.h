#ifndef GENBUILDCONFIGWIDGET_H
#define GENBUILDCONFIGWIDGET_H

#include <QWidget>
#include "../../system/projectConfig.h"
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
public slots:
    void projectLoaded(ProjectConfig* newProject);
};

#endif // GENBUILDCONFIGWIDGET_H
