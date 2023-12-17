
#ifndef EXTERNPROCESSTHREAD_H
#define EXTERNPROCESSTHREAD_H

#include <QThread>
#include <QQueue>
#include <QMutex>

#include <QObject>
#include <QMap>
#include "debuggerProcess.h"
#include "makeProcess.h"
#include "../common/blockingQueue.h"

class ExternProcessThread : public QThread
{
    Q_OBJECT
public:
    class CommendStr{
    public:
        QString commendName;
        QMap<QString, QString> paramMap;
    };


public:   
    explicit ExternProcessThread(QObject *parent = nullptr);
    ~ExternProcessThread();
    void run() override;

    QString makeCommend = "make";


    DebuggerProcess *getDebuggerProcess() const;
    void setDebuggerProcess(DebuggerProcess *newDebuggerProcess);
    MakeProcess *getMakeProcess() const;
    void setMakeProcess(MakeProcess *newMakeProcess);


    BlockingQueue<ExternProcessThread::CommendStr> *getCommendQueue() const;
    void setCommendQueue(BlockingQueue<ExternProcessThread::CommendStr> *newCommendQueue);

private:
    DebuggerProcess* debuggerProcess = nullptr;
    MakeProcess* makeProcess = nullptr;
    QProcess* targetExeCmdProcess = nullptr;
    BlockingQueue<ExternProcessThread::CommendStr>* commendQueue;

signals:
    void taskComplete(QString &taskName, int code, QString &info);
};

#endif // EXTERNPROCESSTHREAD_H
