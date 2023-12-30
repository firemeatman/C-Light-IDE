#include "projectSys.h"

#include <QFile>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

QString ProjectSys::projectConfigFileDefaultName = "CLight.project";


ProjectSys::ProjectSys() {}

bool ProjectSys::createProject(ProjectConfig *project)
{
    if(project == nullptr){
        return false;
    }
    project->stateConfig.isOpen = true;
    projectConfigList.append(project);
    currentProject = project;

    emit projectLoaded(currentProject);

    return true;
}

bool ProjectSys::loadProject(QString& projectDir, QString projectConfigFilePath)
{
    if(projectConfigFilePath.isEmpty()){
        projectConfigFilePath = ProjectSys::projectConfigFileDefaultName;
    }

    // 解析配置文件
    QFile file(projectConfigFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return false;
    }
    ProjectConfig* projectConfig = new ProjectConfig();
    QByteArray data = file.readAll();
    if(!parseConfig(data, projectConfig)){
        delete projectConfig;
        file.close();
        return false;
    }
    if(projectConfig->projectRootDir.isEmpty()){
        projectConfig->projectRootDir = projectDir;
    }

    // 加载进系统
    projectConfig->stateConfig.isOpen = true;
    projectConfigList.append(projectConfig);
    currentProject = projectConfig;
    emit projectLoaded(currentProject);
    file.close();

    return true;
}

bool ProjectSys::openProject(ProjectConfig *project)
{
    if(!projectConfigList.contains(project)){
        return false;
    }
    project->stateConfig.isOpen = true;
    currentProject = project;
    return true;
}

bool ProjectSys::closeProject(ProjectConfig *project)
{
    if(!saveProject(project)){
        return false;
    }

    project->stateConfig.isOpen = false;
    currentProject = nullptr;

    emit projectClosed(project);

    return true;
}

bool ProjectSys::cleanProjectMem(ProjectConfig *project)
{
    if(!projectConfigList.removeOne(project)){
        return false;
    }
    if(currentProject){
        delete currentProject;
        currentProject = nullptr;
    }
    return true;
}


bool ProjectSys::switchProject(QString newProjectDir)
{
    return true;
}

bool ProjectSys::switchProject(ProjectConfig *newProject)
{
    return true;
}

QList<ProjectConfig *> ProjectSys::getProjectConfigList()
{
    return projectConfigList;
}

ProjectConfig *ProjectSys::getCurrentProject()
{
    return currentProject;
}

bool ProjectSys::parseConfig(QByteArray &data, ProjectConfig *projectConfig)
{
    QJsonParseError jerr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &jerr);
    if (doc.isNull())
    {
        qDebug() << jerr.errorString();
        return false;
    }
    QJsonObject jroot = doc.object();
    QJsonValue jvalue;
    // ----一般配置
    projectConfig->projectName = jroot["projectName"].toString("defaultProject");
    projectConfig->projectRootDir = jroot["projectRootDir"].toString();
    jvalue = jroot["projectType"];
    if(jvalue.isNull()){
        projectConfig->projectType = Project_Type::CMAKE_PROJECT;
    }else projectConfig->projectType = (Project_Type)jvalue.toInt();
    projectConfig->ConfigFilePath = jroot["ConfigFilePath"].toString();
    // ----生成&构建配置
    if(projectConfig->projectType == Project_Type::CMAKE_PROJECT){
        QJsonObject cMakeSysConfigJObject = jroot["cMakeSysConfig"].toObject();
        if(!cMakeSysConfigJObject.isEmpty()){
            CMakeSysConfig cmakeSysConfig;

            cmakeSysConfig.c_ComplierPath = cMakeSysConfigJObject["c_ComplierPath"].toString();
            cmakeSysConfig.cxx_ComplierPath = cMakeSysConfigJObject["cxx_ComplierPath"].toString();
            cmakeSysConfig.CMakePath = cMakeSysConfigJObject["CMakePath"].toString();
            cmakeSysConfig.CMakeFilePath = cMakeSysConfigJObject["CMakeFilePath"].toString();
            cmakeSysConfig.buildDir = cMakeSysConfigJObject["buildDir"].toString();
            cmakeSysConfig.installDir = cMakeSysConfigJObject["installDir"].toString();
            cmakeSysConfig.buildsystem = (Buildsystem_Type)cMakeSysConfigJObject["buildsystem"].toInt();
            cmakeSysConfig.buildsystemPath = cMakeSysConfigJObject["buildsystemPath"].toString();

            projectConfig->generateBuildConfig = cmakeSysConfig;
        }
    }else if(projectConfig->projectType == Project_Type::MAKEFILE_PROJECT){
        QJsonObject makeSysConfigJObject = jroot["makeSysConfig"].toObject();
        if(!makeSysConfigJObject.isEmpty()){
            MakeSysConfig makeSysConfig;
            makeSysConfig.c_ComplierPath = makeSysConfigJObject["c_ComplierPath"].toString();
            makeSysConfig.cxx_ComplierPath = makeSysConfigJObject["cxx_ComplierPath"].toString();
            makeSysConfig.makePath = makeSysConfigJObject["CMakeFilePath"].toString();
            makeSysConfig.makeFilePath = makeSysConfigJObject["makeFilePath"].toString();

            projectConfig->generateBuildConfig = makeSysConfig;
        }
    }
    // ----调试配置
    DebugConfig debugConfig;
    QJsonObject debugConfigJObject = jroot["debugConfig"].toObject();
    if(!debugConfigJObject.isEmpty()){
        jvalue = debugConfigJObject["type"];
        if(jvalue.isNull()){
            debugConfig.type = Debuger_Type::GDB;
        }else debugConfig.type = (Debuger_Type)jvalue.toInt();
        debugConfig.debugerPath = debugConfigJObject["debugerPath"].toString();

        projectConfig->debugConfig = debugConfig;
    }

    return true;
}

bool ProjectSys::saveProject(ProjectConfig *project)
{
    // json序列化
    QJsonObject projectJsonObject;
    QJsonObject genbuildJsonObject;
    QJsonObject debugObject;
    QJsonDocument jsonDoc;
    projectJsonObject.insert("projectName", project->projectName);
    projectJsonObject.insert("projectRootDir", project->projectRootDir);
    projectJsonObject.insert("projectType", project->projectType);
    projectJsonObject.insert("ConfigFilePath", project->ConfigFilePath);

    genbuildJsonObject.insert("c_ComplierPath", project->generateBuildConfig.c_ComplierPath);
    genbuildJsonObject.insert("cxx_ComplierPath", project->generateBuildConfig.cxx_ComplierPath);
    if(project->projectType == Project_Type::CMAKE_PROJECT){
        CMakeSysConfig* cMakeSysConfig = static_cast<CMakeSysConfig*>(&(project->generateBuildConfig));
        genbuildJsonObject.insert("CMakePath", cMakeSysConfig->CMakePath);
        genbuildJsonObject.insert("CMakeFilePath", cMakeSysConfig->CMakeFilePath);
        genbuildJsonObject.insert("buildsystemPath", cMakeSysConfig->buildsystemPath);
        genbuildJsonObject.insert("buildsystem", cMakeSysConfig->buildsystem);
        genbuildJsonObject.insert("buildDir", cMakeSysConfig->buildDir);
        genbuildJsonObject.insert("installDir", cMakeSysConfig->installDir);
        projectJsonObject.insert("cMakeSysConfig", QJsonValue(genbuildJsonObject));
    }else if(project->projectType == Project_Type::MAKEFILE_PROJECT){
        MakeSysConfig* makeSysConfig = static_cast<MakeSysConfig*>(&(project->generateBuildConfig));
        genbuildJsonObject.insert("makePath", makeSysConfig->makePath);
        genbuildJsonObject.insert("makeFilePath", makeSysConfig->makeFilePath);
        projectJsonObject.insert("makeSysConfig", QJsonValue(genbuildJsonObject));
    }

    debugObject.insert("type", project->debugConfig.type);
    debugObject.insert("debugerPath", project->debugConfig.debugerPath);
    projectJsonObject.insert("debugConfig", QJsonValue(debugObject));

    jsonDoc.setObject(projectJsonObject);
    QByteArray data = jsonDoc.toJson();

    // 写入文件
    QFile file(project->ConfigFilePath);
    if (!file.open(QIODevice::WriteOnly)){
        return false;
    }
    file.write(data);
    file.close();

    return true;
}

