#ifndef PROJECTSYS_H
#define PROJECTSYS_H

#include <QObject>
#include <QList>
#include <QString>

#include "projectConfig.h"


class ProjectSys : public QObject
{
    Q_OBJECT
public:
    ProjectSys(QObject *parent = nullptr);
    ~ProjectSys();

    bool createProject(ProjectConfig* project);
    bool createProject(QString& name, QString& rootDir, Project_Type type, ProjectConfig* project);
    bool loadProject(QString& projectDir, QString projectConfigFilePath = "");
    bool openProject(ProjectConfig* project);
    bool closeProject(ProjectConfig* project);
    bool cleanProjectMem(ProjectConfig* project);

    // 不支持
    bool switchProject(QString newProjectDir);
    bool switchProject(ProjectConfig* newProject);

    QList<ProjectConfig*> getProjectConfigList();
    ProjectConfig* getCurrentProject();


private:
    QList<ProjectConfig*> projectConfigList;
    ProjectConfig* currentProject = nullptr;

    static QString projectConfigFileDefaultName;
    static QString CmakeListTemplate;

    bool parseConfig(QByteArray& data, ProjectConfig* projectConfig);
    bool saveProject(ProjectConfig* project);

signals:
    void projectLoaded(ProjectConfig* newProject);
    void projectClosed(ProjectConfig* closedProject);

};

#endif // PROJECTSYS_H
