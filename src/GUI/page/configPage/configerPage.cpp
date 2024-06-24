#include "configerPage.h"

ConfigerPage::ConfigerPage(QWidget *parent)
    : QMainWindow{parent}
{
    buildConfigerwidget = new BuildConfigerForm(this);

    this->setCentralWidget(buildConfigerwidget);
    buildConfigerwidget->show();
}
