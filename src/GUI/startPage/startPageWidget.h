#ifndef STARTPAGEWIDGET_H
#define STARTPAGEWIDGET_H

#include <QWidget>

class CreateProjectDialog;

namespace Ui {
class StartPageWidget;
}

class StartPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartPageWidget(QWidget *parent = nullptr);
    ~StartPageWidget();

private:
    Ui::StartPageWidget *ui;

    CreateProjectDialog* createProjectDialog = nullptr;

public slots:
    void _on_clicked_openBtn();
    void _on_clicked_createBtn();
    void _on_acceptCreate();
    void _on_rejecptCreate();
};

#endif // STARTPAGEWIDGET_H
