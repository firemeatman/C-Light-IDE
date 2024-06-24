#ifndef CONFIGERPAGE_H
#define CONFIGERPAGE_H

#include <QMainWindow>
#include "buildConfigerForm.h"

class ConfigerPage : public QMainWindow
{
    Q_OBJECT
public:
    explicit ConfigerPage(QWidget *parent = nullptr);

    BuildConfigerForm* buildConfigerwidget;

signals:
};

#endif // CONFIGERPAGE_H
