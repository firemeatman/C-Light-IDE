#ifndef CMAKEPROCESS_H
#define CMAKEPROCESS_H

#include <QObject>
#include <QProcess>
class CmakeProcess : public QObject
{
    Q_OBJECT
public:
    typedef struct{
        QString cmakePath;
        QString cmakeFilePath;
        QString buildDir;
        QString installDir;
        QString buildsystemName;
        QString buildsystemPath;
        QString cComplierPath;
        QString cxxComplierPath;
    } Cmake_Param;

public:
    explicit CmakeProcess(QObject *parent = nullptr);
    ~ CmakeProcess();

    void setCmakeParam(Cmake_Param& params);

    bool build();
    bool install();


    QProcess *getProcess() const;
    void setProcess(QProcess *newProcess);

private:
    QProcess* process = nullptr;
    Cmake_Param cmakeParam;

signals:
    void msgRecved(QString &str);

public slots:
    void _on_recvCmdOut();
    void _on_recvCmdError();

};

#endif // CMAKEPROCESS_H
