#include "project.h"
#include <QFile>
#include <QFileInfo>

QString Project::configkey_projectName = "projectName";
QString Project::configkey_projectType = "projectType";
QString Project::configkey_generateConfig = "generateConfig";
QString Project::configkey_complier_path = "complierPath";
QString Project::configkey_complier_name = "complierName ";

Project::Project() {
    state = ProjectState::Emputy;
}

bool Project::configProject(QString &configFilePath)
{
    bool flag = false;
    if(!configFilePath.isEmpty()){
        QFileInfo fileInfo(configFilePath);
        this->configFilePath = configFilePath;
        this->projectRootDir = fileInfo.absolutePath();
    }
    if(this->configFilePath.isEmpty()){
        return flag;
    }

    // 解析配置文件
    QFile file(this->configFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return flag;
    }
    QByteArray data = file.readAll();
    file.close();
    if(parseJsonConfig(data)){
        flag = true;
        QJsonObject jRoot = this->getRootConfigJson();
        this->name = jRoot[Project::configkey_projectName].toString();
    }

    return flag;
}

bool Project::saveProject(QString& configFilePath)
{
    bool flag = false;
    if(!configFilePath.isEmpty()){
        this->configFilePath = configFilePath;
    }
    QJsonObject jRoot = this->getRootConfigJson();
    this->name = jRoot[Project::configkey_projectName].toString();
    QFileInfo fileInfo(configFilePath);
    this->projectRootDir = fileInfo.absolutePath();

    QFile file(this->configFilePath);
    if (!file.open(QIODevice::WriteOnly)){
        return flag;
    }
    QByteArray data = this->configJsonDoc.toJson();
    file.write(data);
    file.close();
    flag = true;

    return flag;
}

QJsonObject Project::getRootConfigJson()
{
    return this->configJsonDoc.object();
}

void Project::setRootConfigJson(QJsonObject &jObject)
{
    this->configJsonDoc.setObject(jObject);
}

bool Project::parseJsonConfig(QByteArray &data)
{
    QJsonParseError jerr;
    this->configJsonDoc = QJsonDocument::fromJson(data, &jerr);
    if (this->configJsonDoc.isNull())
    {
        qDebug() << jerr.errorString();
        return false;
    }
    return true;

}
