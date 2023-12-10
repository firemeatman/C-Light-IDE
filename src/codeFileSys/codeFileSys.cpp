
#include "codeFileSys.h"
#include <QFile>

CodeFileSys::CodeFileSys(QObject *parent)
    : QObject{parent}
{

}

CodeFileSys::~CodeFileSys()
{
//    for( CodeFileSys::CodeFileInfo* v : opendCodeFileList){
//        delete v;
//    }
    qDeleteAll(opendCodeFileList);
opendCodeFileList.clear();
}

bool CodeFileSys::saveAllFile()
{
    bool flag = true;
    for(CodeFileInfo* v : opendCodeFileList) {
        if(v->isNeedSave){
            QFile file(v->path);
            if(!file.open(QIODeviceBase::WriteOnly)){
                flag = false;
            }else{
                file.write(v->data);
                v->isNeedSave = false;
                QString text = v->item->text();
                int start = (text.size() - 1) - 3;
                if(start < 0){
                    flag = false;
                }else{
                    v->item->setText(text.mid(start));
                }
            }
            file.close();
        }
    }
    return flag;
}

bool CodeFileSys::updateCache(CodeFileInfo *fileInfo, QByteArray &data)
{
    for(CodeFileInfo* v : opendCodeFileList) {
        if(v == fileInfo){
            v->data = data;
            if(!v->isNeedSave){
                v->isNeedSave = true;
                QString text = v->item->text();
                text.append("[*]");
                v->item->setText(text);
            }
            return true;
        }
    }

    return false;
}




