#include "projectManager.h"

ProjectManager::ProjectManager(QObject* parent)
    : QObject(parent)
{

}

ProjectManager::~ProjectManager()
{
    //qDeleteAll(projectList);
    projectList.clear();
}

bool ProjectManager::addProject(std::shared_ptr<Project> project)
{
    if(project == nullptr) return false;

    this->projectList.push_back(project);
    emit projectAdded(project);
    return true;
}

bool ProjectManager::removeProject(std::shared_ptr<Project> project)
{
    if(project == nullptr) return false;

    int size = projectList.size();
    for(int i=0; i<size ; i++){
        if(projectList.at(i).get() == project.get()){
            projectList.erase(projectList.begin() + i);
            break;
        }
    }
    emit projectRemoved(project);
    return true;
}

bool ProjectManager::switchProject(std::shared_ptr<Project> project)
{
    bool flag = false;
    if(project == nullptr) return flag;

    int size = projectList.size();
    for(int i=0; i<size ; i++){
        if(projectList.at(i).get() == project.get()){
            this->currentProject = projectList[i];
            this->currentIndex = i;
            flag = true;
            break;
        }
    }
    return flag;
}

bool ProjectManager::switchProject(int index)
{
    bool flag = false;
    if(index < 0 || index >= projectList.size()){
        return flag;
    }
    this->currentProject = projectList[index];
    this->currentIndex = index;
    flag = true;

    return flag;
}

bool ProjectManager::isProjectExist(QString &configFilePath)
{
    int size = projectList.size();
    for(int i=0; i<size ; i++){
        if(projectList.at(i)->configFilePath == configFilePath){
            return true;
        }
    }
    return false;
}


int ProjectManager::getCurrentIndex() const
{
    return currentIndex;
}

std::shared_ptr<Project> ProjectManager::getCurrentProject() const
{
    return currentProject;
}


