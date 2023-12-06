
#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H


#include <QString>
#include "../GUI/mainwindow.h"
#include "../GUI/commonWidget/terminalWidget.h"
#include "../terminalSys/terminalSysteam.h"
//class MainWindow;
//class TerminalWidget;
//class TerminalSysteam;

class GlobalData{
public:

    GlobalData();

    static MainWindow* global_mainWindow;
    static TerminalWidget* global_terminalWidget;
    static TerminalSysteam* global_terminalSysteam;

    static QString ComplierPath;
    static QString DebugerPath;
    static QString MakeFilePath;

};



#endif // GLOBAL_DATA_H
