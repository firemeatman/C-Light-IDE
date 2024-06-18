#include "usefulTool.h"
#include <QFileInfo>

UsefulTool::UsefulTool() {}

QStringList UsefulTool::userSelectFile(QString& windowTitle, QFileDialog::FileMode fileMode,
                                                 QString currentDir, QWidget* parent)
{
    QFileDialog *fileDialog = new QFileDialog(parent);
    QFileInfo fileInfo(currentDir);
    fileDialog->setWindowTitle(windowTitle);
    if(!currentDir.isEmpty()){
        if(fileInfo.isDir()){
            fileDialog->setDirectory(currentDir);
        }else if(fileInfo.isFile()){
            fileDialog->setDirectory(fileInfo.absolutePath());
        }

    }
    fileDialog->setOption(QFileDialog::DontUseNativeDialog);
    fileDialog->setFileMode(fileMode);
    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
    }
    if(parent == nullptr){
        fileDialog->deleteLater();
    }
    return fileNames;
}
