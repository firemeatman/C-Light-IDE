
#ifndef MAKEPROCESS_H
#define MAKEPROCESS_H


#include <QObject>
#include <QProcess>

class MakeProcess : public QObject
{
    Q_OBJECT
public:
    explicit MakeProcess(QObject *parent = nullptr);
    ~MakeProcess();
    void startProcess(QString& exePath, QString& workDir);
    void closeProcess();

    bool make(QString &makeExePath, QString &mkFileDir, QString &mkFileName);
    bool clean(QString &makeExePath, QString &mkFileDir, QString &mkFileName);

    QProcess *getProcess() const;

private:
    QProcess* process = nullptr;

signals:
    void msgRecved(QString &str);

public slots:
    void _on_recvCmdOut();
    void _on_recvCmdError();


signals:

};

#endif // MAKEPROCESS_H
