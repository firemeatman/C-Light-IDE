#ifndef MODELDATADEF_H
#define MODELDATADEF_H

#include <QString>

class ModelDataDef
{
public:
    ModelDataDef();
};

typedef struct HistoryProject_s{
    QString name;
    QString rootPath;
}HistoryProject;

#endif // MODELDATADEF_H
