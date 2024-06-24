#ifndef BUILDCONFIGERFORM_H
#define BUILDCONFIGERFORM_H

#include <QWidget>

namespace Ui {
class BuildConfigerForm;
}

class BuildConfigerForm : public QWidget
{
    Q_OBJECT

public:
    explicit BuildConfigerForm(QWidget *parent = nullptr);
    ~BuildConfigerForm();

private:
    Ui::BuildConfigerForm *ui;
};

#endif // BUILDCONFIGERFORM_H
