
#ifndef EXTERNPROCESSTHREAD_H
#define EXTERNPROCESSTHREAD_H

#include <QThread>
#include <QQueue>
#include <QMutex>

#include <QObject>
#include <QMap>
#include "debuggerProcess.h"
#include "makeProcess.h"
#include "cmakeProcess.h"
#include "../common/blockingQueue.h"

class ExternProcessThread : public QThread
{
    Q_OBJECT
public:
    class CommendStr{
    public:
        QString commendName;
        QMap<QString, QString> paramMap;
        QString from;
    };


public:   
    explicit ExternProcessThread(QObject *parent = nullptr);
    ~ExternProcessThread();
    void run() override;

    DebuggerProcess *getDebuggerProcess() const;
    void setDebuggerProcess(DebuggerProcess *newDebuggerProcess);
    MakeProcess *getMakeProcess() const;
    void setMakeProcess(MakeProcess *newMakeProcess);
    BlockingQueue<ExternProcessThread::CommendStr> *getCommendQueue() const;
    void setCommendQueue(BlockingQueue<ExternProcessThread::CommendStr> *newCommendQueue);

    CmakeProcess *getCmakeProcess() const;
    void setCmakeProcess(CmakeProcess *newCmakeProcess);

private:
    DebuggerProcess* debuggerProcess = nullptr;
    MakeProcess* makeProcess = nullptr;
    CmakeProcess* cmakeProcess = nullptr;
    QProcess* targetExeCmdProcess = nullptr;
    BlockingQueue<ExternProcessThread::CommendStr>* commendQueue;

    void makeHandel(ExternProcessThread::CommendStr& commend, int* code);
    void cleanHandel(ExternProcessThread::CommendStr& commend, int* code);
    void runTargetHandel(ExternProcessThread::CommendStr& commend, int* code);

signals:
    void taskComplete(QString &taskName, int code, QString &info, QString& from);
    void taskStart(QString &taskName, QString& from);
};

#endif // EXTERNPROCESSTHREAD_H
