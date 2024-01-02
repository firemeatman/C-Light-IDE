#ifndef CREATEPROJECTDIALOG_H
#define CREATEPROJECTDIALOG_H

#include <QDialog>
#include <QString>

#include "../../system/projectConfig.h"
namespace Ui {
class CreateProjectDialog;
}

class CreateProjectDialog : public QDialog
{
    Q_OBJECT

public:

    typedef struct{
        QString projetName;
        Project_Type type;
        QString root;
    } Back_Params;

    explicit CreateProjectDialog(QWidget *parent = nullptr);
    ~CreateProjectDialog();

    void getBack_Params(Back_Params* data);

private:
    Ui::CreateProjectDialog *ui;

public slots:
    void _on_clicked_rootBtn();
};

#endif // CREATEPROJECTDIALOG_H
