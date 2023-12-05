
#include "newBulidFile.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

NewBulidFile::NewBulidFile(QWidget *parent):QDialog(parent){
    QLabel *fileNameLabel = new QLabel("文件名", this);
    QLabel *fileNameTypeLabel = new QLabel("文件类型", this);
    fileNameEdit = new QLineEdit(this);
    fileNameTypeBox = new QComboBox(this);
    fileNameTypeBox->addItem(".txt"); //这里可以多加几个Item,方法类似，用于新建文件时指定文件的类型
    okButton = new QPushButton("确定",this);
    cancalButton = new QPushButton("取消",this);

    QHBoxLayout *Hlayout1 = new QHBoxLayout();
    Hlayout1->addWidget(fileNameLabel);
    Hlayout1->addWidget(fileNameEdit);
    QHBoxLayout *Hlayout2 = new QHBoxLayout();
    Hlayout2->addWidget(fileNameTypeLabel);
    Hlayout2->addWidget(fileNameTypeBox);
    QHBoxLayout *Hlayout3 = new QHBoxLayout();
    Hlayout3->addWidget(okButton);
    Hlayout3->addWidget(cancalButton);
    QVBoxLayout *MainVlayout = new QVBoxLayout(this); //布局使用嵌套布局
    MainVlayout->addLayout(Hlayout1);
    MainVlayout->addLayout(Hlayout2);
    MainVlayout->addLayout(Hlayout3);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
}

NewBulidFile::~NewBulidFile()
{

}
