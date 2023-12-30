#ifndef PROJECTCONFIG_H
#define PROJECTCONFIG_H

#include <QString>

typedef enum{
    CMAKE_PROJECT,
    MAKEFILE_PROJECT,
} Project_Type;

typedef enum{
    Ninja,
    Make,
    MSBuild,
}Buildsystem_Type;

typedef enum{
    GDB,
    CDB,
}Debuger_Type;

class DebugConfig
{
public:
    DebugConfig();

    QString debugerPath;
    Debuger_Type type;
};

class GenerateBuildConfig
{
public:
    GenerateBuildConfig();
    QString c_ComplierPath;
    QString cxx_ComplierPath;
};

class CMakeSysConfig : public GenerateBuildConfig
{
public:
    CMakeSysConfig();

    QString CMakePath;
    QString CMakeFilePath;
    QString buildDir;
    QString installDir;
    Buildsystem_Type buildsystem;
    QString buildsystemPath;
};

class MakeSysConfig : public GenerateBuildConfig
{
public:
    MakeSysConfig();
    QString makePath;
    QString makeFilePath;
};

class StateConfig{
public:
    bool isOpen = false;
    // lastOpenedTime
};

/*
项目配置文件格式：
{
    "projectName":"testproject",
    "projectRootDir",
    "projectType",
    "ConfigFilePath",

    "CMakeSysConfig":{

    },
    "makeSysConfig":{

    },
    "debugConfig":{

    }
}

*/
class ProjectConfig
{
public:
    ProjectConfig();

    QString projectName;
    QString projectRootDir;
    Project_Type projectType;
    QString ConfigFilePath;

    StateConfig stateConfig;
    GenerateBuildConfig generateBuildConfig;
    DebugConfig debugConfig;
};
#endif // PROJECTCONFIG_H
