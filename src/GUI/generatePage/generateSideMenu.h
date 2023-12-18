#ifndef GENERATESIDEMENU_H
#define GENERATESIDEMENU_H

#include <QWidget>

namespace Ui {
class GenerateSideMenu;
}

class GenerateSideMenu : public QWidget
{
    Q_OBJECT

public:
    explicit GenerateSideMenu(QWidget *parent = nullptr);
    ~GenerateSideMenu();

private:
    Ui::GenerateSideMenu *ui;

public slots:
    void _on_clicked_makeConfBtn();
    void _on_clicked_debugConfBtn();
};

#endif // GENERATESIDEMENU_H
