
#ifndef CODEFILESYS_H
#define CODEFILESYS_H


#include <QObject>
#include <QList>
#include <QListWidget>

class CodeFileSys : public QObject
{
    Q_OBJECT
public:
    explicit CodeFileSys(QObject *parent = nullptr);
    ~CodeFileSys();

    class CodeFileInfo{
    public:
        QString path;
        QString realName;
        QString itemName;
        QListWidgetItem* item;
        QByteArray data;
    };

    QList<CodeFileSys::CodeFileInfo*> opendCodeFileList;


private:




//signals:

};

#endif // CODEFILESYS_H
