#include "usefulTool.h"

UsefulTool::UsefulTool() {}

QStringList UsefulTool::userSelectFile(QString& windowTitle, QFileDialog::FileMode fileMode,
                                                 QString currentDir, QWidget* parent)
{
    QFileDialog *fileDialog = new QFileDialog(parent);
    fileDialog->setWindowTitle(windowTitle);
    if(!currentDir.isEmpty()){
        fileDialog->setDirectory(currentDir);
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
