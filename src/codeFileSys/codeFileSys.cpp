
#include "codeFileSys.h"

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




