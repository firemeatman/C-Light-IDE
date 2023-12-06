
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SideMenuWidget;
class StartPageWidget;
class CodePageEditWidget;
class CodeTreeSideWidget;
class GeneratePageWidget;
class TerminalWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    CodeTreeSideWidget *getCodeTreeSideWidget() const;

private:
    Ui::MainWindow *ui;

    QDockWidget* codeTreeSidedockWidget;
    QDockWidget* terminaldockWidget;

    SideMenuWidget* sideMenuWidget;
    StartPageWidget* startPageWidget;
    CodePageEditWidget* codePageEditWidget;
    CodeTreeSideWidget* codeTreeSideWidget;
    TerminalWidget* terminalWidget;
    GeneratePageWidget* generatePageWidget;

public slots:
    void _on_clicked_StartBtn();
    void _on_clicked_CodeBtn();
    void _on_clicked_GenerateBtn();
    void _on_clicked_RunBtn();
};

#endif // MAINWINDOW_H
