#ifndef STARTPAGEWIDGET_H
#define STARTPAGEWIDGET_H

#include <QWidget>
#include "../../window/actionWindow/createProjectDialog.h"
#include "historyListWidget.h"
#include "../../../common/global_data.h"

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
    CreateProjectDialog* createDialog;
    HistoryListWidget* hisWidget;


public slots:
    void _on_clicked_openBtn();
    void _on_clicked_createBtn();
    void _on_create_finished(int res);
    void _on_projectAdded(std::shared_ptr<Project> project);
};

#endif // STARTPAGEWIDGET_H
