
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
        bool isNeedSave = false;
        QByteArray data;
    };

    QList<CodeFileSys::CodeFileInfo*> opendCodeFileList;

    bool saveFileData(CodeFileSys::CodeFileInfo* fileInfo);
    bool saveFileData(QListWidgetItem* item);
    bool saveAllFile();
    //bool updateCache(QString& path, QByteArray& data);
    bool updateCache(CodeFileSys::CodeFileInfo* fileInfo, QByteArray& data);

private:




//signals:

};

#endif // CODEFILESYS_H
