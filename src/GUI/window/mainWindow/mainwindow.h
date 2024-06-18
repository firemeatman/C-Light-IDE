
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include  <QPushButton>
#include <QVariantMap>

class SideMenuWidget;
class StartPageWidget;
class CodePageEditWidget;
class CodeTreeSideWidget;
class CodeFileListWidget;

class ProjectConfigSideMenu;
class ProjectConfigWidget;
class GenBuildConfigWidget;
class debugConfigWidget;

class MakeInfoWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class WindowPageRoute{
    StartPage,
    CodePage,
    ConfigPage,
};

// 该类没有UI部件的所有权
class Page{
public:

    typedef struct DockInfo_s
    {
        QDockWidget* dock_p;
        bool settedState;
        DockInfo_s() {}
    }DockInfo;

    WindowPageRoute routeName;
    QWidget* centralWindow = nullptr;
    QList<DockInfo> dockList;

    explicit Page(WindowPageRoute route, QWidget* centralWindow = nullptr);
    void addDock(QDockWidget* dock, bool state = true);
};

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QList<Page*> pageList;
    bool jump(WindowPageRoute route, QVariantMap& param);

private:
    Ui::MainWindow *ui;

public:
    QDockWidget* codeTreeSidedockWidget = nullptr;
    QDockWidget* makeOutdockWidget = nullptr;
    QDockWidget* codeFileListdockWidget = nullptr;
    QDockWidget* projectConfigSideMenuDockWidget = nullptr;

    SideMenuWidget* sideMenuWidget = nullptr;
    StartPageWidget* startPageWidget = nullptr;
    CodePageEditWidget* codePageEditWidget = nullptr;
    CodeTreeSideWidget* codeTreeSideWidget = nullptr;
    CodeFileListWidget* codeFileListWidget = nullptr;
    MakeInfoWidget* makeInfoWidget = nullptr;

    ProjectConfigSideMenu* projectConfigSideMenu = nullptr;
    ProjectConfigWidget* projectConfigWidget = nullptr;
    GenBuildConfigWidget* genBuildConfigWidget = nullptr;
    debugConfigWidget* _debugConfigWidget = nullptr;

    QPushButton* programOutBtn = nullptr;
    QPushButton* makeOutBtn = nullptr;

signals:
    void pageSwitched(WindowPageRoute route, QVariantMap param);

public slots:


    void _on_clicked_programOutBtn();
    void _on_clicked_makeOutBtn();

};

#endif // MAINWINDOW_H
