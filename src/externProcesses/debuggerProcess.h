
#ifndef DEBUGGERPROCESS_H
#define DEBUGGERPROCESS_H


#include <QObject>
#include <QProcess>

class DebuggerProcess : public QObject
{
    Q_OBJECT
public:
    explicit DebuggerProcess(QObject *parent = nullptr);
    void startProcess(QString& exePath);
    void closeProcess();
    // 附加待调试程序
    bool targetBeingDebuggedExe(QString& DebuggedExePath);
    // 断点
    bool setBreakPoint(QString& fileName, QString& lineNum);
    bool deleBreakPoint(QString& fileName, QString& lineNum);
    // 运行
    bool startDebuggedExe();
    bool runDebuggedExe();
    bool next();
    bool step();
    bool continueRun();
    // 监视变量
    bool getVariableValue(QString& variable);
    // 监视栈
    bool getStackInfo();

    // 结束调试
    bool endDebug();

private:
    QProcess* process = nullptr;
signals:

};

#endif // DEBUGGERPROCESS_H
