
#ifndef CODEFILESYS_H
#define CODEFILESYS_H


#include <QObject>
#include <QMap>
#include <QListWidget>

class CodeFileSys : public QObject
{
    Q_OBJECT
public:
    explicit CodeFileSys(QObject *parent = nullptr);
    ~CodeFileSys();

    class FileInfo{
    public:
        QString name;
        QListWidgetItem* item;
        QByteArray data;
    };

    bool addFileCache(QString& filePath, QByteArray& data);
    bool addFileInfo(QString& filePath, CodeFileSys::FileInfo* fileInfo);
    bool containFile(QString& filePath);
    CodeFileSys::FileInfo* findFile(QString& filePath);
    CodeFileSys::FileInfo* findFile(QListWidgetItem* item);
    QString getfilePath(QListWidgetItem* item);
    QString getfilePath(CodeFileSys::FileInfo* fileInfo);
    void removeFileCache(QString& filePath);
    bool updateFileCache(QString& filePath, QByteArray& data);


    QMap<QString, CodeFileSys::FileInfo*> getOpenedFileMap() const;
    void setOpenedFileMap(const QMap<QString, CodeFileSys::FileInfo*> &newOpenedFileMap);

private:
    QMap<QString, CodeFileSys::FileInfo*> openedFileMap;



//signals:

};

#endif // CODEFILESYS_H
