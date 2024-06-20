#ifndef CREATEFILEDIALOG_H
#define CREATEFILEDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class CreateFileDialog;
}

class CreateFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateFileDialog(QWidget *parent = nullptr);
    ~CreateFileDialog();

    QString defalutDir;

private:
    Ui::CreateFileDialog *ui;

public slots:
    void _on_fileClicked();
    void _on_accept();
};

#endif // CREATEFILEDIALOG_H
