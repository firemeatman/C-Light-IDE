#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QObject>
#include <vector>
#include <QString>
#include <memory>
#include "project.h"

class ProjectManager : public QObject
{
    Q_OBJECT
public:
    ProjectManager(QObject* parent = nullptr);
    ~ProjectManager();

    bool addProject(std::shared_ptr<Project> project);
    bool removeProject(std::shared_ptr<Project> project);
    bool switchProject(std::shared_ptr<Project> project);
    bool switchProject(int index);
    bool isProjectExist(QString& configFilePath);

    int getCurrentIndex() const;
    std::shared_ptr<Project> getCurrentProject() const;

private:
    std::vector<std::shared_ptr<Project>> projectList;
    std::shared_ptr<Project> currentProject = nullptr;
    int currentIndex = 0;
signals:
    void projectAdded(std::shared_ptr<Project> project);
    void projectRemoved(std::shared_ptr<Project> project);
};

#endif // PROJECTMANAGER_H
