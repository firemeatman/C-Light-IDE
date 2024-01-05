#include "projectSys.h"

#include <QFile>
#include <QDir>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>



QString ProjectSys::projectConfigFileDefaultName = "CLight_Project.json";
QString ProjectSys::CmakeListTemplate = "cmake_minimum_required (VERSION 3.8)\n\
project (\"test\" C)\n\
# 启动对C11标准的支持\n\
# set(CMAKE_C_STANDARD 11)\n\
# 显式要求指明支持C标准\n\
# set(CMAKE_C_STANDARD_REQUIRED True)\n\
#设置c的编译选项\n\
set (CMAKE_C_FLAGS \"${CMAKE_C_FLAGS} -std=c11\")\n\
# 将源代码添加到此项目的可执行文件。\n\
add_executable (${PROJECT_NAME}\n\
                   src/main.c src/math/my_math.c src/math/my_math.h\n\
                   )";

ProjectSys::ProjectSys(QObject *parent)
    : QObject{parent}
{

}

ProjectSys::~ProjectSys()
{
    for(ProjectConfig* v : projectConfigList){
        delete v;
    }
    projectConfigList.clear();
}

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

bool ProjectSys::createProject(QString &name, QString &rootDir, Project_Type type, ProjectConfig *project)
{
    project = new ProjectConfig();
    project->projectName = name;
    project->projectType = type;
    project->projectRootDir = rootDir;

    // 创建项目配置文件
    QDir nativeRootDir(rootDir);
    QString configFilePath = nativeRootDir.absoluteFilePath(ProjectSys::projectConfigFileDefaultName);
    QFile configFile(configFilePath);
    if (!configFile.open(QIODevice::WriteOnly)){
        if(project == nullptr){
            delete project;
        }
        return false;
    }
    project->ConfigFilePath = configFilePath;
    configFile.close();

    // 创建根据项目类型创建构建所需的文件
    QString buildFilePath;
    QString outStr;
    if(project->projectType == Project_Type::CMAKE_PROJECT){
        buildFilePath = nativeRootDir.absoluteFilePath("CMakeLists.txt");
        outStr = ProjectSys::CmakeListTemplate;
    }else if(project->projectType == Project_Type::MAKEFILE_PROJECT){
        buildFilePath = nativeRootDir.absoluteFilePath("makefile");
        outStr = ProjectSys::CmakeListTemplate;
    }

    QFile buildFile(buildFilePath);
    if (!buildFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        if(project == nullptr){
            delete project;
        }
        return false;
    }
    QTextStream textOut(&buildFile);
    textOut << outStr;
    buildFile.close();

    // 保存一次项目配置，打开项目，并存入系统管理
    if(!saveProject(project)){
        if(project == nullptr){
            delete project;
        }
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
        QDir nativeRootDir(projectDir);
        projectConfigFilePath = nativeRootDir.absoluteFilePath(ProjectSys::projectConfigFileDefaultName);
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
    if(project == nullptr){
        return false;
    }
    if(!projectConfigList.contains(project)){
        return false;
    }
    project->stateConfig.isOpen = true;
    currentProject = project;
    return true;
}

bool ProjectSys::closeProject(ProjectConfig *project)
{
    if(project == nullptr){
        return false;
    }
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
    if(project == nullptr){
        return false;
    }
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
    if(projectConfig == nullptr){
        return false;
    }
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
            cmakeSysConfig.targetName = cMakeSysConfigJObject["targetName"].toString();
            cmakeSysConfig.CMakePath = cMakeSysConfigJObject["CMakePath"].toString();
            cmakeSysConfig.CMakeFilePath = cMakeSysConfigJObject["CMakeFilePath"].toString();
            cmakeSysConfig.buildDir = cMakeSysConfigJObject["buildDir"].toString();
            cmakeSysConfig.installDir = cMakeSysConfigJObject["installDir"].toString();
            cmakeSysConfig.buildsystem = (Buildsystem_Type)cMakeSysConfigJObject["buildsystem"].toInt();
            cmakeSysConfig.buildsystemPath = cMakeSysConfigJObject["buildsystemPath"].toString();

            projectConfig->cmakeConfig = cmakeSysConfig;
        }
    }else if(projectConfig->projectType == Project_Type::MAKEFILE_PROJECT){
        QJsonObject makeSysConfigJObject = jroot["makeSysConfig"].toObject();
        if(!makeSysConfigJObject.isEmpty()){
            MakeSysConfig makeSysConfig;
            makeSysConfig.c_ComplierPath = makeSysConfigJObject["c_ComplierPath"].toString();
            makeSysConfig.cxx_ComplierPath = makeSysConfigJObject["cxx_ComplierPath"].toString();
            makeSysConfig.targetName = makeSysConfigJObject["targetName"].toString();
            makeSysConfig.makePath = makeSysConfigJObject["CMakeFilePath"].toString();
            makeSysConfig.makeFilePath = makeSysConfigJObject["makeFilePath"].toString();

            projectConfig->makeSysConfig = makeSysConfig;
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
    if(project == nullptr){
        return false;
    }
    // json序列化
    QJsonObject projectJsonObject;
    QJsonObject genbuildJsonObject;
    QJsonObject debugObject;
    QJsonDocument jsonDoc;
    projectJsonObject.insert("projectName", project->projectName);
    projectJsonObject.insert("projectRootDir", project->projectRootDir);
    projectJsonObject.insert("projectType", project->projectType);
    projectJsonObject.insert("ConfigFilePath", project->ConfigFilePath);

    if(project->projectType == Project_Type::CMAKE_PROJECT){
        CMakeSysConfig& cMakeSysConfig = project->cmakeConfig;
        genbuildJsonObject.insert("c_ComplierPath", cMakeSysConfig.c_ComplierPath);
        genbuildJsonObject.insert("cxx_ComplierPath", cMakeSysConfig.cxx_ComplierPath);
        genbuildJsonObject.insert("targetName", cMakeSysConfig.targetName);
        genbuildJsonObject.insert("CMakePath", cMakeSysConfig.CMakePath);
        genbuildJsonObject.insert("CMakeFilePath", cMakeSysConfig.CMakeFilePath);
        genbuildJsonObject.insert("buildsystemPath", cMakeSysConfig.buildsystemPath);
        genbuildJsonObject.insert("buildsystem", cMakeSysConfig.buildsystem);
        genbuildJsonObject.insert("buildDir", cMakeSysConfig.buildDir);
        genbuildJsonObject.insert("installDir", cMakeSysConfig.installDir);
        projectJsonObject.insert("cMakeSysConfig", QJsonValue(genbuildJsonObject));
    }else if(project->projectType == Project_Type::MAKEFILE_PROJECT){
        MakeSysConfig& makeSysConfig = project->makeSysConfig;
        genbuildJsonObject.insert("c_ComplierPath", makeSysConfig.c_ComplierPath);
        genbuildJsonObject.insert("cxx_ComplierPath", makeSysConfig.cxx_ComplierPath);
        genbuildJsonObject.insert("targetName", makeSysConfig.targetName);
        genbuildJsonObject.insert("makePath", makeSysConfig.makePath);
        genbuildJsonObject.insert("makeFilePath", makeSysConfig.makeFilePath);
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

