#ifndef EDITCODEMANAGER_H
#define EDITCODEMANAGER_H

#include <QObject>
#include <QList>
#include <QMap>
#include "../project/projectManager.h"
// enum class FileSate{
//     Open,

// };

class FileStruct{
public:
    QString name;
    QString path;
    bool isChanged;

    std::shared_ptr<Project> project;

    FileStruct(QString& name, QString& path, std::shared_ptr<Project> project)
        :name(name),path(path),isChanged(false),project(project){};
    FileStruct():isChanged(false),project(nullptr){};
};

class EditCodeManager : public QObject
{
    Q_OBJECT
public:
    explicit EditCodeManager(QObject *parent = nullptr);
    QMap<QString, FileStruct> openedfileMap;

    bool addOpenedFile(FileStruct& file);
    bool removeOpenedFile(QString& path);
    bool editFile(QString& path);
    bool setFileChanged(QString& path, bool isChanged);
    bool setFileName(QString& path, QString& name);
    bool saveFile(QString& path);

signals:
    void fileisChangedChanged(FileStruct file);
    void fileNameChanged(FileStruct file);
    void fileEditing(FileStruct file);
    void fileOpened(FileStruct file);
    void fileClosed(FileStruct file);
    void fileSave(FileStruct file);
public slots:
    void _on_projectRemoved(std::shared_ptr<Project> project);
};

#endif // EDITCODEMANAGER_H
