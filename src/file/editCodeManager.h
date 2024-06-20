#ifndef EDITCODEMANAGER_H
#define EDITCODEMANAGER_H

#include <QObject>
#include <QList>
#include <QMap>
#include "../project/project.h"

// enum class FileSate{
//     Open,

// };

class FileStruct{
public:
    QString name;
    QString path;
    bool isChanged;
};

class EditCodeManager : public QObject
{
    Q_OBJECT
public:
    explicit EditCodeManager(QObject *parent = nullptr);
    QMap<QString, FileStruct> openedfileMap;

    bool addOpenedFile(QString& path, QString& name);
    bool removeOpenedFile(QString& path);
    bool editFile(QString& path);
    bool setFileChanged(QString& path, bool isChanged);

signals:
    void fileisChangedChanged(FileStruct file);
    void fileEditing(FileStruct file);
    void fileOpened(FileStruct file);
    void fileClosed(FileStruct file);
public slots:
    void _on_projectRemoved(std::shared_ptr<Project> project);
};

#endif // EDITCODEMANAGER_H
