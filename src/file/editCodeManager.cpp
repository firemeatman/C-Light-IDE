#include "editCodeManager.h"

EditCodeManager::EditCodeManager(QObject *parent)
    : QObject{parent}
{}

bool EditCodeManager::addOpenedFile(QString &path, QString& name)
{
    bool flag = false;
    if(openedfileMap.contains(path)){
        emit fileOpened(openedfileMap[path]);
        flag = true;
        return flag;
    }
    FileStruct file;
    file.path = path;
    file.name = name;
    file.isChanged = false;
    openedfileMap.insert(path, file);
    flag = true;
    emit fileOpened(file);

    return flag;
}

bool EditCodeManager::removeOpenedFile(QString &path)
{
    bool flag = false;
    if(!openedfileMap.contains(path)){
        return flag;
    }
    FileStruct file = openedfileMap.value(path);
    openedfileMap.remove(path);
    flag = true;
    emit fileClosed(file);

    return flag;
}

bool EditCodeManager::editFile(QString &path)
{
    bool flag = false;
    if(!openedfileMap.contains(path)){
        return flag;
    }
    flag = true;
    emit fileEditing(openedfileMap[path]);

    return flag;
}

bool EditCodeManager::setFileChanged(QString &path, bool isChanged)
{
    bool flag = false;
    if(!openedfileMap.contains(path)){
        return flag;
    }
    openedfileMap[path].isChanged = isChanged;
    flag = true;
    emit fileisChangedChanged(openedfileMap[path]);

    return flag;
}

void EditCodeManager::_on_projectRemoved(std::shared_ptr<Project> project)
{

}
