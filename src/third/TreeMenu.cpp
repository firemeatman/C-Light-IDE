#include "TreeMenu.h"


#include <QTreeWidget>

#include <QDir>
#include <QScrollBar>
#include <QMenu>
#include <QHeaderView>
#include <QApplication>
#include <QProcess>
#include <QMessageBox>


TreeMenu::TreeMenu(QWidget *parent):QTreeWidget(parent){
    this->setObjectName("TreeMenu");
    this->verticalScrollBar()->setObjectName("TreeMenuVerticl");
    this->horizontalScrollBar()->setObjectName("TreeMenuHorizontal");

    this->setColumnCount(1);
    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    this->setAutoScroll(true);
    this->header()->setVisible(false);   //隐藏横向表头

    this->setFrameStyle(QFrame::Sunken);
    this->setAnimated(true); //展开折叠动画


    QFile qssFile("TreeMenu.qss");
    if(qssFile.open(QFile::ReadOnly)){
        this->setStyleSheet(qssFile.readAll());
    }
    qssFile.close();

    newFileWidget = new NewBulidFile(this);
    newFileWidget->setWindowFlags(newFileWidget->windowFlags()| Qt::Dialog);

    connect(newFileWidget->okButton,SIGNAL(clicked(bool)),this,SLOT(bulidNewFileSlot(bool)));
    connect(newFileWidget->cancalButton,SIGNAL(clicked(bool)),this,SLOT(closeBuildFileSlot(bool)));

    newDirWidget = new NewBuildfolder(this);
    newDirWidget->setWindowFlags(newDirWidget->windowFlags()| Qt::Dialog);
    connect(newDirWidget->okButton,SIGNAL(clicked(bool)),this,SLOT(buildNewDirSlot(bool)));
    connect(newDirWidget->cancalButton,SIGNAL(clicked(bool)),this,SLOT(cancelDirSlot(bool)));
    // 创建右击文件夹的菜单栏
    dirMenu = new QMenu(this);
    dirMenu->addAction("新建文件");
    dirMenu->addAction("重命名");
    dirMenu->addSeparator();
    dirMenu->addAction("新建文件夹");
    dirMenu->addAction("删除文件夹");
    dirMenu->addAction("在文件夹中查找             ");
    dirMenu->addAction("关闭项目");
    // 创建右击文件的菜单栏
    fileMenu = new QMenu(this);
    fileMenu->addAction("重命名");
    fileMenu->addAction("删除文件");
    fileMenu->addAction("打开所在文件夹");
    connect(dirMenu,SIGNAL(triggered(QAction*)),this,SLOT(tempActionInformation(QAction*)));
    connect(fileMenu,SIGNAL(triggered(QAction*)),this,SLOT(tempActionInformation(QAction*)));

    connect(this,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(itemPressedSlot(QTreeWidgetItem*,int)));
    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(DoubleClickpath(QTreeWidgetItem*,int)));
    connect(this,SIGNAL(collapseItemSignal(const QTreeWidgetItem*)),this,SLOT(collapseItem(const QTreeWidgetItem*)));

}

TreeMenu::~TreeMenu()
{
    if(this->nowItem != nullptr){
        this->nowItem->takeChildren();
    }
    if(this->root != nullptr){
        this->root->takeChildren();
    }
}

void TreeMenu::openFileTree(QString path)
{
    QDir rootdir(path);
    if(root != nullptr){
        this->takeTopLevelItem(0);
        delete root;
        root = nullptr;
    }
    root = new QTreeWidgetItem();
    this->addTopLevelItem(root);
    root->setText(0,rootdir.dirName());
    root->setIcon(0,QIcon("../resource/folder.png"));
    root->setToolTip(0, path);
    FindFile(&rootdir,root);
    QApplication::processEvents(); //防止界面假死
    root->setExpanded(true);
}

// 创建文件树的根
void TreeMenu::CreateTopItem(QString path){
    QDir rootdir(path);
    root = new QTreeWidgetItem();
    this->addTopLevelItem(root);
    root->setText(0,rootdir.dirName());
    root->setIcon(0,QIcon("../resource/folder.png"));
    root->setToolTip(0, path);
    FindFile(&rootdir,root);
    QApplication::processEvents(); //防止界面假死
    root->setExpanded(true);
}
// 创建文件树
void TreeMenu::FindFile(QDir *path,QTreeWidgetItem *parent){
    QApplication::processEvents(); //防止界面假死
    QStringList AllDirName = path->entryList();  //返回所有文件名
    QString PathContent = path->absolutePath();
    int startIndex = 0;
    for(startIndex = 0; startIndex<AllDirName.size(); startIndex++){
        if(startIndex>=2){
            break;
        }
        if(AllDirName[startIndex] != "." && AllDirName[startIndex] != ".."){
            break;
        }
    }
    for(int i = startIndex;i < AllDirName.size(); i++)
    {
        QFileInfo FileInfo(PathContent+"/"+AllDirName[i]);
        if(FileInfo.isFile())
        {
            QTreeWidgetItem *child = new QTreeWidgetItem(parent); //创建对象并添加所属关系
            child->setIcon(0,QIcon("../resource/file.png")); //设置Item的图标，也可以通过QSS设置。
            child->setText(0,AllDirName[i]); //设置Item的名字及所扫描到的文件名。
            child->setToolTip(0,PathContent+"/"+AllDirName[i]);
        }
        else if(FileInfo.isDir())
        {
            QTreeWidgetItem *child = new QTreeWidgetItem(parent);  //创建对象并添加所属关系。
            child->setIcon(0,QIcon("../resource/folder.png")); //设置Item的图标，也可以通过QSS设置。
            child->setText(0,AllDirName[i]);  //设置Item的名字及所扫描到的文件名。
            child->setToolTip(0,PathContent+"/"+AllDirName[i]); //鼠标移动到Item上所显示的内容，这里为绝对路径。
        }
    }
}
// 双击槽函数检测是文件还是目录。执行打开文件或者打开文件夹
void TreeMenu::DoubleClickpath(QTreeWidgetItem *item, int /*column*/){
    QString absolute_Path = item->toolTip(0);
    QFileInfo *FileInfo = new QFileInfo(absolute_Path);
    this->resizeColumnToContents(0);

    if(FileInfo->isFile())
    {
        // 发送打开文件信号
        emit openFileSignal(absolute_Path,FileInfo->baseName(),item);
    }
    else{
        // 打开文件夹

        if(item->childCount() == 0){
            QDir dir(absolute_Path);
            FindFile(&dir,item);
        }
    }
}
// 鼠标右键单击文件或文件夹时所执行的操作
void TreeMenu::itemPressedSlot(QTreeWidgetItem * pressedItem, int column){
    this->resizeColumnToContents(0);
    nowItem = pressedItem;
    nowCol = column;
    if(qApp->mouseButtons() == Qt::RightButton)   //判断是否为右键
    {
        QString absolute_Path = pressedItem->toolTip(0);
        QFileInfo FileInfo(absolute_Path);
        if(FileInfo.isFile()){
            fileMenu->exec(QCursor::pos()); //显示右键菜单栏
        }
        else{
            dirMenu->exec(QCursor::pos());  //显示右键菜单栏
        }
    }
}
// 右击菜单栏执行操作的具体方法
void TreeMenu::tempActionInformation(QAction *act){
    if(act->text()=="关闭项目"){
        QTreeWidgetItem *item = this->currentItem();
        QTreeWidgetItem* parItem=item->parent();
        if(parItem==0)
        {
            delete item;
        }
        else {
            parItem->removeChild(item) ;
            delete item;
        }
    }
    if(act->text() == "删除文件"){
        QTreeWidgetItem *item = this->currentItem();
        delete item;
    }
    if(act->text() == "删除文件夹"){
        QTreeWidgetItem *item = this->currentItem();
        delete item;
    }
    if(act->text() == "重命名"){
        emit renameSignal();
    }
    if(act->text() == "打开所在文件夹"){
        QString path = nowItem->toolTip(0);
        int index=0;
        for(int i=0;i<path.length();i++){
            if(path[i] == '/')
                index=i;
        }
        QString filePath = path.mid(0,index).replace("/","\\");
        QProcess::startDetached("explorer "+filePath);//打开上面获取的目录

    }
    if(act->text() == "新建文件"){
        newFileWidget->setModal(true);
        newFileWidget->show();
    }
    if(act->text()=="新建文件夹"){
        newDirWidget->setModal(true);
        newDirWidget->exec();
    }
}
// 文件夹折叠的实现主要为顶部按钮提供方法
void TreeMenu::buttonCollapseItem(){
    QTreeWidgetItem *t = this->currentItem();
    if(t==0)
        return;
    if(t->childCount()==0){
        QTreeWidgetItem *p = t->parent();
        if(p==0){
            return;
        }
        else{
            emit collapseItemSignal(p); //折叠文件夹
        }
    }
    else{
        emit collapseItemSignal(t);
    }
}

NewBulidFile *TreeMenu::getNewFileWidget() const
{
    return newFileWidget;
}

void TreeMenu::setNewFileWidget(NewBulidFile *newNewFileWidget)
{
    newFileWidget = newNewFileWidget;
}

NewBuildfolder *TreeMenu::getNewDirWidget() const
{
    return newDirWidget;
}

void TreeMenu::setNewDirWidget(NewBuildfolder *newNewDirWidget)
{
    newDirWidget = newNewDirWidget;
}
// 创建文件的具体实现
void TreeMenu::bulidNewFileSlot(bool /*flag*/){
    QString fileName = newFileWidget->fileNameEdit->text();
    QString filetype = newFileWidget->fileNameTypeBox->currentText();
    if(fileName==""){
        QMessageBox::warning(this, tr("警告"),
                             tr("文件名不能为空"));
        return;
    }
    QString tempName = fileName+filetype;
    QString path = nowItem->toolTip(0)+"/"+tempName;
    QFile file(path);
    if(file.exists()){
        QMessageBox::warning(this, tr("警告"),
                             tr("文件已存在"));
        return;
    }
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    file.close();
    QTreeWidgetItem *child = new QTreeWidgetItem(nowItem);
    child->setText(0,tempName);
    child->setIcon(0,QIcon("../resource/file.png"));
    child->setToolTip(0,path);
    newFileWidget->close();
}
//取消按钮的具体实现
void TreeMenu::closeBuildFileSlot(bool /*flag*/){
    newFileWidget->close();
}

// 创建文件夹的具体实现
void TreeMenu::buildNewDirSlot(bool /*flag*/){
    QString dirName = newDirWidget->fileNameEdit->text();
    if(dirName==""){
        QMessageBox::warning(this, tr("Application"),
                             tr("文件名不能为空"));
        return;
    }
    QString path = nowItem->toolTip(0)+"/"+dirName;
    QDir temp;
    bool exist = temp.exists(path);
    if(exist){
        QMessageBox::warning(this,tr("创建文件夹"),tr("文件夹已经存在！"));
        return;
    }
    temp.mkdir(path);
    QTreeWidgetItem *child = new QTreeWidgetItem(nowItem);
    child->setText(0,dirName);
    child->setIcon(0,QIcon("../resource/folder.png"));
    child->setToolTip(0,path);
    newDirWidget->close();
}
// 取消按钮的具体实现
void TreeMenu::cancelDirSlot(bool /*flag*/){
    newDirWidget->close();
}

