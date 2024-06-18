#ifndef CREATEPROJECTDIALOG_H
#define CREATEPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class CreateProjectDialog;
}

class CreateProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProjectDialog(QWidget *parent = nullptr);
    ~CreateProjectDialog();


private:
    Ui::CreateProjectDialog *ui;

public slots:
    void _on_clicked_rootBtn();
    void _on_acceptCreate();
};

#endif // CREATEPROJECTDIALOG_H
