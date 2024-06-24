
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariantMap>
#include <QPushButton>
#include <QStackedWidget>

class SideMenuWidget;
class StartPageWidget;
class CodePageEditWidget;
class CodeTreeSideWidget;
class CodeFileListWidget;

class MakeInfoWidget;
class CodePage;
class ConfigerPage;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class WindowPageRoute{
    StartPage,
    CodePage,
    ConfigPage,
};
enum class MainWindowDock{
    BuildDock,
    WrongDock,
};

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool jump(WindowPageRoute route, QVariantMap& param);
    bool switchDockWidget(MainWindowDock dock, bool enable);

private:
    Ui::MainWindow *ui;

public:

    QStackedWidget* stackWidget = nullptr;

    CodePage* codePage = nullptr;
    ConfigerPage* configerPage = nullptr;
    StartPageWidget* startPageWidget = nullptr;

    QDockWidget* makeOutdockWidget = nullptr;
    SideMenuWidget* sideMenuWidget = nullptr;
    MakeInfoWidget* makeInfoWidget = nullptr;
    // QDockWidget* projectConfigSideMenuDockWidget = nullptr;
    // ProjectConfigSideMenu* projectConfigSideMenu = nullptr;
    // ProjectConfigWidget* projectConfigWidget = nullptr;
    // GenBuildConfigWidget* genBuildConfigWidget = nullptr;
    // debugConfigWidget* _debugConfigWidget = nullptr;

    QPushButton* programOutBtn = nullptr;
    QPushButton* makeOutBtn = nullptr;

signals:
    void pageSwitched(WindowPageRoute route, QVariantMap param);

public slots:


    void _on_clicked_programOutBtn();
    void _on_clicked_makeOutBtn();

};

#endif // MAINWINDOW_H
