#ifndef PROJECTCONFIGSIDEMENU_H
#define PROJECTCONFIGSIDEMENU_H

#include <QWidget>

namespace Ui {
class ProjectConfigSideMenu;
}

class ProjectConfigSideMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectConfigSideMenu(QWidget *parent = nullptr);
    ~ProjectConfigSideMenu();

private:
    Ui::ProjectConfigSideMenu *ui;

public slots:
    void _on_clicked_projectConfigBtn();
    void _on_clicked_genBuildConfigBtn();
    void _on_clicked_debugConfigBtn();
};

#endif // PROJECTCONFIGSIDEMENU_H
