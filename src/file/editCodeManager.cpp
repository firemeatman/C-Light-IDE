#include "editCodeManager.h"

EditCodeManager::EditCodeManager(QObject *parent)
    : QObject{parent}
{}

bool EditCodeManager::addOpenedFile(FileStruct& file)
{
    bool flag = false;
    if(openedfileMap.contains(file.path)){
        emit fileOpened(openedfileMap[file.path]);
        flag = true;
        return flag;
    }
    file.isChanged = false;
    openedfileMap.insert(file.path, file);
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

bool EditCodeManager::setFileName(QString &path, QString &name)
{
    bool flag = false;
    if(!openedfileMap.contains(path)){
        return flag;
    }
    openedfileMap[path].name = name;
    flag = true;
    emit fileNameChanged(openedfileMap[path]);

    return flag;
}

bool EditCodeManager::saveFile(QString &path)
{
    bool flag = false;
    if(!openedfileMap.contains(path)){
        return flag;
    }

    FileStruct file =  openedfileMap[path];
    if(file.isChanged){
        flag = true;
        emit fileSave(openedfileMap[path]);
    }
    return flag;
}

void EditCodeManager::_on_projectRemoved(std::shared_ptr<Project> project)
{

}
