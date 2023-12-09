
#include "codeFileSys.h"

CodeFileSys::CodeFileSys(QObject *parent)
    : QObject{parent}
{

}

CodeFileSys::~CodeFileSys()
{
    QList<CodeFileSys::FileInfo*> valueList = openedFileMap.values();
    for(CodeFileSys::FileInfo* v : valueList){
        delete v;
    }
}

bool CodeFileSys::addFileCache(QString &filePath, QByteArray &data)
{
    if(openedFileMap.contains(filePath)){
        return false;
    }
    CodeFileSys::FileInfo* fileInfo = new CodeFileSys::FileInfo();
    fileInfo->data = data;
    openedFileMap.insert(filePath, fileInfo);
    return true;
}

bool CodeFileSys::addFileInfo(QString &filePath, FileInfo *fileInfo)
{
    if(openedFileMap.contains(filePath)){
        return false;
    }
    openedFileMap.insert(filePath, fileInfo);
    return true;
}

bool CodeFileSys::containFile(QString &filePath)
{
    return openedFileMap.contains(filePath);
}

CodeFileSys::FileInfo* CodeFileSys::findFile(QString &filePath)
{
   return openedFileMap.value(filePath);
}

CodeFileSys::FileInfo* CodeFileSys::findFile(QListWidgetItem *item)
{
   QList<CodeFileSys::FileInfo*> valueList = openedFileMap.values();
   for(CodeFileSys::FileInfo* v : valueList){
       if(v->item == item){
           return v;
       }
   }
   return nullptr;
}

QString CodeFileSys::getfilePath(QListWidgetItem *item)
{
   QList<CodeFileSys::FileInfo*> valueList = openedFileMap.values();
   for(CodeFileSys::FileInfo* v : valueList){
       if(v->item == item){
           return openedFileMap.key(v);
       }
   }
   return "";
}

QString CodeFileSys::getfilePath(FileInfo *fileInfo)
{
   return openedFileMap.key(fileInfo);
}

void CodeFileSys::removeFileCache(QString &filePath)
{
   if(openedFileMap.contains(filePath)){
       delete openedFileMap.value(filePath);
       openedFileMap.remove(filePath);
   }

}

bool CodeFileSys::updateFileCache(QString &filePath, QByteArray &data)
{
   if(openedFileMap.contains(filePath)){
       openedFileMap.value(filePath)->data = data;
       return true;
   }
   return false;
}



QMap<QString, CodeFileSys::FileInfo*> CodeFileSys::getOpenedFileMap() const
{
    return openedFileMap;
}

void CodeFileSys::setOpenedFileMap(const QMap<QString, CodeFileSys::FileInfo*> &newOpenedFileMap)
{
    openedFileMap = newOpenedFileMap;
}



