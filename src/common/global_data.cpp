#include "global_data.h"


MainWindow* GlobalData::global_mainWindow = nullptr;
TerminalWidget* GlobalData::global_terminalWidget = nullptr;

TerminalSysteam* GlobalData::global_terminalSysteam = nullptr;

QString GlobalData::ComplierPath = "";
QString GlobalData::DebugerPath = "";
QString GlobalData::MakeFilePath = "";

GlobalData::GlobalData()
{

}
