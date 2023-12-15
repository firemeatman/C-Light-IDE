
#ifndef EXTERNPROCESSTHREAD_H
#define EXTERNPROCESSTHREAD_H

#include <QThread>
#include <QQueue>
#include <QMutex>

#include <QObject>
#include "debuggerProcess.h"
#include "makeProcess.h"
#include "../common/blockingQueue.h"

class ExternProcessThread : public QThread
{
    Q_OBJECT
public:   
    explicit ExternProcessThread(QObject *parent = nullptr);
    ~ExternProcessThread();
    void run() override;

    QString makeCommend = "make";


    DebuggerProcess *getDebuggerProcess() const;
    void setDebuggerProcess(DebuggerProcess *newDebuggerProcess);
    MakeProcess *getMakeProcess() const;
    void setMakeProcess(MakeProcess *newMakeProcess);
    BlockingQueue<QString> *getCommendQueue() const;
    void setCommendQueue(BlockingQueue<QString> *newCommendQueue);

private:
    DebuggerProcess* debuggerProcess = nullptr;
    MakeProcess* makeProcess = nullptr;
    BlockingQueue<QString>* commendQueue;

signals:
    void taskComplete(QString &taskName, int code, QString &info);
};

#endif // EXTERNPROCESSTHREAD_H
