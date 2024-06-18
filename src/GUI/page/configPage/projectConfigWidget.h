#ifndef PROJECTCONFIGWIDGET_H
#define PROJECTCONFIGWIDGET_H

#include <QWidget>

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

    void _on_projectNameEdited();
    void _on_targetNameEdited();
    void _on_clicked_rootBtn();
};

#endif // PROJECTCONFIGWIDGET_H
