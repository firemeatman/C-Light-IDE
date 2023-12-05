
#ifndef NEWBUILDFOLDER_H
#define NEWBUILDFOLDER_H


#include <QDialog>
#include <QLineEdit>

// 创建文件夹时弹出的窗体
class NewBuildfolder : public QDialog
{
    Q_OBJECT
public:
    NewBuildfolder(QWidget *parent=0);
    ~NewBuildfolder();
    QLineEdit *fileNameEdit;
    QPushButton *okButton;
    QPushButton *cancalButton;
};
#endif // NEWBUILDFOLDER_H
