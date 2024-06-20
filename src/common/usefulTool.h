#ifndef USEFULTOOL_H
#define USEFULTOOL_H

#include <QFileDialog>

class UsefulTool
{
public:
    UsefulTool();

    static QStringList userSelectFile(QString& windowTitle, QFileDialog::FileMode fileMode,
                                         QString currentDir = "", QWidget* parent = nullptr);

};

#endif // USEFULTOOL_H
