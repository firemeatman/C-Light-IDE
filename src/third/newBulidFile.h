
#ifndef NEWBULIDFILE_H
#define NEWBULIDFILE_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

// 创建文件时 弹出的窗体
class NewBulidFile : public QDialog{
    Q_OBJECT
public:
    NewBulidFile(QWidget *parent=0);
    ~NewBulidFile();
    QLineEdit *fileNameEdit;
    QComboBox *fileNameTypeBox;
    QPushButton *okButton;
    QPushButton *cancalButton;
};
#endif // NEWBULIDFILE_H
