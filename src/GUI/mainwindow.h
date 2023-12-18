
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include  <QPushButton>

class SideMenuWidget;
class StartPageWidget;
class CodePageEditWidget;
class CodeTreeSideWidget;
class GenerateSideMenu;
class MakeConfigWidget;
class DebugConfigWidget;

class CodeFileListWidget;
class MakeInfoWidget;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    QDockWidget *getCodeTreeSidedockWidget() const;
    QDockWidget *getMakeOutdockWidget() const;
    QDockWidget *getCodeFileListdockWidget() const;
    SideMenuWidget *getSideMenuWidget() const;
    StartPageWidget *getStartPageWidget() const;
    CodePageEditWidget *getCodePageEditWidget() const;
    CodeTreeSideWidget *getCodeTreeSideWidget() const;
    CodeFileListWidget *getCodeFileListWidget() const;
    MakeInfoWidget *getMakeInfoWidget() const;

    QPushButton *getProgramOutBtn() const;
    QPushButton *getMakeOutBtn() const;

    QDockWidget *getGenerateSideMenuDockWidget() const;
    GenerateSideMenu *getGenerateSideMenuWidget() const;
    MakeConfigWidget *getMakeConfigWidget() const;
    DebugConfigWidget *getDebugConfigWidget() const;

private:
    Ui::MainWindow *ui;

    QDockWidget* codeTreeSidedockWidget;
    QDockWidget* makeOutdockWidget;
    QDockWidget* codeFileListdockWidget;
    QDockWidget* generateSideMenuDockWidget;

    SideMenuWidget* sideMenuWidget;
    StartPageWidget* startPageWidget;
    CodePageEditWidget* codePageEditWidget;
    CodeTreeSideWidget* codeTreeSideWidget;
    CodeFileListWidget* codeFileListWidget;
    MakeInfoWidget* makeInfoWidget = nullptr;
    GenerateSideMenu* generateSideMenuWidget;
    MakeConfigWidget* makeConfigWidget;
    DebugConfigWidget* debugConfigWidget;

    QPushButton* programOutBtn;
    QPushButton* makeOutBtn;



public slots:
    void _on_clicked_StartBtn();
    void _on_clicked_CodeBtn();
    void _on_clicked_GenerateBtn();

    void _on_clicked_programOutBtn();
    void _on_clicked_makeOutBtn();

};

#endif // MAINWINDOW_H
