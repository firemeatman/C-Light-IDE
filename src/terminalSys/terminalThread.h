
#ifndef TERMINALTHREAD_H
#define TERMINALTHREAD_H

#include <QThread>
#include <QMutex>
#include <QString>
#include <QQueue>
#include <QProcess>

class TerminalThread : public QThread
{
    Q_OBJECT
public:
    TerminalThread();
    void run() override;

    void addCommond(QString& str);
    void setCmdProcess(QProcess* cmdProcess);

private:
    QProcess* cmdProcess = nullptr;
    QString commondStr;
    QQueue<QString> commondQueue;
    QMutex queneMutex;
    QMutex cmdMutex;
};

#endif // TERMINALTHREAD_H
