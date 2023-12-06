
#ifndef TERMINALSYSTEAM_H
#define TERMINALSYSTEAM_H

#include <QString>
#include <QObject>
#include <QProcess>
//class TerminalThread;

class TerminalSysteam : public QObject
{
    Q_OBJECT

public:
    TerminalSysteam(QObject *parent = nullptr);
    ~TerminalSysteam();

    void startTerminal();
    void closeTerminal();
    bool sendCommand(QString& str);

public slots:
    void _on_recvCmdOut();
    void _on_recvCmdError();

private:
    QProcess* cmdProcess = nullptr;
    //TerminalThread* terminalThread = nullptr;
};

#endif // TERMINALSYSTEAM_H
