#ifndef PROJECT_H
#define PROJECT_H

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
enum class ProjectState{
    Emputy,
    Loading,
    Ready,
};
// enum class ProjectType{
//     GccLike,
//     CMake,
// };


/*
    projectName
    projectType
    generateConfig--- complierPath、complierName、outExeDir、outExeRoot、outExeName



    buildConfig---

    debugConfig---

 */

/**
 * @brief The Project class
 */

class Project
{
public:
    Project();


    bool configProject(QString& configFilePath);
    bool saveProject(QString& configFilePath);
    QJsonObject getRootConfigJson();
    void setRootConfigJson(QJsonObject& jObject);

    ProjectState state;
    QString name;
    QString projectRootDir;
    QString configFilePath;
    QJsonDocument configJsonDoc;
private:
    bool parseJsonConfig(QByteArray &data);

public:
    static QString configkey_projectName;
    static QString configkey_projectType;
    static QString configkey_generateConfig;
    static QString configkey_complier_path;
    static QString configkey_complier_name;


};

#endif // PROJECT_H
