#include "codeTreeSideWidget.h"
#include "ui_codeTreeSideWidget.h"

#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QLineEdit>
#include "../../../common/global_data.h"

CodeTreeSideWidget::CodeTreeSideWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodeTreeSideWidget)
{
    ui->setupUi(this);
    treeWidget = new QTreeWidget(this);
    treeWidget->setColumnCount(1);
    treeWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    treeWidget->setAutoScroll(true);
    treeWidget->header()->setVisible(false);   //隐藏横向表头
    treeWidget->setFrameStyle(QFrame::Sunken);
    //treeWidget->setAnimated(false); //展开折叠动画

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(treeWidget);

    // 菜单设置
    fileMenu = new QMenu(this);
    fileMenu->addAction("关闭项目"); // 0
    fileMenu->addAction("新文件"); // 1
    addfileMenu = new QMenu("创建更多文件",this);
    addfileMenu->addAction("空白文件");
    addfileMenu->addAction(".h文件");
    addfileMenu->addAction(".c文件");
    addfileMenu->addAction(".cpp文件");
    addfileMenu->addAction("c++类");
    fileMenu->addMenu(addfileMenu);
    fileMenu->addAction("创建文件夹");
    fileMenu->addAction("重命名");
    fileMenu->addAction("删除文件");
    fileMenu->addAction("删除文件夹");

    connect(this->treeWidget, &QTreeWidget::itemDoubleClicked, this, &CodeTreeSideWidget::_on_itemDoubleCliced);
    connect(this->treeWidget, &QTreeWidget::itemPressed, this, &CodeTreeSideWidget::_on_itemPressed);
    connect(GlobalData::projectManager, &ProjectManager::projectAdded, this, &CodeTreeSideWidget::_on_ProjectAdded);
    connect(GlobalData::projectManager, &ProjectManager::projectRemoved, this, &CodeTreeSideWidget::_on_ProjectRemoved);

    connect(fileMenu, &QMenu::triggered, this, &CodeTreeSideWidget::_on_fileMenuTriggered);

}

CodeTreeSideWidget::~CodeTreeSideWidget()
{
    delete ui;
}

void CodeTreeSideWidget::loadProjectFileTree(std::shared_ptr<Project> project)
{
    CodeTreeWidgetItem* rootItem = new CodeTreeWidgetItem();
    this->treeWidget->addTopLevelItem(rootItem);

    rootItem->project = project;
    rootItem->setText(0,project->name);
    rootItem->setIcon(0,QIcon(":/icons/resource/icons/file.png"));
    rootItem->setToolTip(0, project->projectRootDir);
    rootItem->setExpanded(true);

    QDir dir(project->projectRootDir);
    loadChildFile(dir, rootItem);
}

void CodeTreeSideWidget::loadChildFile(QDir &parentDir, CodeTreeWidgetItem *parent)
{

    QApplication::processEvents(); //防止界面假死
    if(!parent) return;
    QStringList childFileNameList = parentDir.entryList();  //返回所有文件名
    QString parentPath = parentDir.absolutePath();
    int childFileListSize = childFileNameList.count();

    for(int i=0; i<childFileListSize; i++)
    {
        QString fileNameStr = childFileNameList.at(i);
        if(fileNameStr == "." || fileNameStr == ".."){
            continue;
        }
        QFileInfo fileInfo(parentPath+"/"+fileNameStr);
        CodeTreeWidgetItem *child = new CodeTreeWidgetItem(parent);
        child->project = parent->project;
        child->setText(0,fileNameStr);
        child->setToolTip(0,fileInfo.absoluteFilePath());
        if(fileInfo.isFile())
        {
            child->setIcon(0,QIcon(":/icons/resource/icons/file.png"));
        }
        else if(fileInfo.isDir())
        {
            child->setIcon(0,QIcon(":/icons/resource/icons/folder.png"));
        }
    }
}

void CodeTreeSideWidget::clearChildren(CodeTreeWidgetItem *parent)
{
    if(parent == nullptr) return;

    int count = parent->childCount();
    for(int i=count-1; i>=0; i--)
    {
        CodeTreeWidgetItem* childItem = dynamic_cast<CodeTreeWidgetItem*>(parent->child(i));
        parent->removeChild(childItem);
        SAFE_DELE_P(childItem);
    }
}

QString CodeTreeSideWidget::genFileSoleName(QDir &dir, QString name)
{
    QString tempName = name;
    int count = 1;
    while(dir.exists(tempName)){
        if(count > 20){
            tempName = "";
            break;
        }
        tempName = name + (QString::number(count));
        count++;
    }

    return tempName;
}


CodeTreeWidgetItem *CodeTreeSideWidget::addChildFileItem(QString &path, CodeTreeWidgetItem *parent)
{
    QFileInfo fileInfo(path);
    if(!fileInfo.exists() || parent == nullptr){
        return nullptr;
    }
    CodeTreeWidgetItem *child = new CodeTreeWidgetItem(parent);
    child->project = parent->project;
    child->setText(0,fileInfo.fileName());
    child->setToolTip(0,fileInfo.absoluteFilePath());
    if(fileInfo.isFile())
    {
        child->setIcon(0,QIcon(":/icons/resource/icons/file.png"));
    }
    else if(fileInfo.isDir())
    {
        child->setIcon(0,QIcon(":/icons/resource/icons/folder.png"));
    }
    return child;
}

void CodeTreeSideWidget::startEditTreeItem(CodeTreeWidgetItem *item, int colum)
{
    if(!item) return;
    this->currentEditNameItem = item;
    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setText(item->text(colum));
    lineEdit->selectAll();
    lineEdit->setFocus();
    connect(lineEdit, &QLineEdit::editingFinished, this, &CodeTreeSideWidget::_on_nameEditingFinished);
    treeWidget->setItemWidget(item, colum, lineEdit);
}

void CodeTreeSideWidget::_on_itemDoubleCliced(QTreeWidgetItem *item)
{

    QString path = item->toolTip(0);
    CodeTreeWidgetItem* item_p = dynamic_cast<CodeTreeWidgetItem*>(item);
    QFileInfo fileInfo(path);
    if(fileInfo.isDir()){ // 文件夹：加载子文件
        clearChildren(item_p);
        QDir dir(fileInfo.absoluteFilePath());
        loadChildFile(dir, item_p);
    }else if(fileInfo.isFile()){ // 文件：打开文件
        QString name = item_p->text(0);
        FileStruct file(name,path,item_p->project);
        GlobalData::editCodeManager->addOpenedFile(file);
    }
}

void CodeTreeSideWidget::_on_itemPressed(QTreeWidgetItem *item, int column)
{
    if(qApp->mouseButtons() != Qt::RightButton){
        return;
    }

    QString filePath = item->toolTip(0);
    QFileInfo fileInfo(filePath);
    int type = 0;
    if(item->parent() == nullptr){
        type = SelectItemType::ProjectRoot;
    }
    if(fileInfo.isFile()){
        type |=  SelectItemType::File;
    }else if(fileInfo.isDir()){
        type |=  SelectItemType::Dir;
    }

    QList<QAction*> actionList= fileMenu->actions();
    for(auto action: actionList){
        action->setVisible(true);
    }
    for(auto action: actionList){
        if(action->text() == "关闭项目"){
            if(!(type & SelectItemType::ProjectRoot)){
                action->setVisible(false);
            }
        }else if(action->text() == "重命名"){
            if(type & SelectItemType::ProjectRoot || type & SelectItemType::Dir){
                action->setVisible(false);
            }
        }else if(action->text() == "删除文件"){
            if(type & SelectItemType::ProjectRoot || type & SelectItemType::Dir){
                action->setVisible(false);
            }
        }else if(action->text() == "删除文件夹"){
            if(type & SelectItemType::ProjectRoot || type & SelectItemType::File){
                action->setVisible(false);
            }
        }
    }


    fileMenu->exec(QCursor::pos());
}

void CodeTreeSideWidget::_on_fileMenuTriggered(QAction *action)
{
    QString text = action->text();
    QTreeWidgetItem* item = this->treeWidget->currentItem();
    CodeTreeWidgetItem* item_p = dynamic_cast<CodeTreeWidgetItem*>(item);
    QString filePath = item->toolTip(0);

    if(text == "关闭项目"){
        std::shared_ptr<Project> project = item_p->project;
        if(project){
            GlobalData::projectManager->removeProject(project);
        }
    }else if(text == "新文件"){
        // 设置新文件路径
        QFileInfo fileInfo(filePath);
        QString path;
        if(fileInfo.isFile()){
            QDir dir = fileInfo.absoluteDir();
            QString newName = genFileSoleName(dir, this->defaultFileName);
            if(newName.isEmpty()){
                QMessageBox::warning(this, "创建失败", "文件名生成失败！", QMessageBox::NoButton);
                return;
            }else{
                path = dir.filePath(this->defaultFileName);
            }

        }else if(fileInfo.isDir()){
            QDir dir(filePath);
            QString newName = genFileSoleName(dir, this->defaultFileName);
            if(newName.isEmpty()){
                QMessageBox::warning(this, "创建失败", "文件名生成失败！", QMessageBox::NoButton);
                return;
            }else{
                path = filePath + "/" + newName;
            }
        }
        // 创建文件，更新UI显示
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly)){
            QMessageBox::warning(this, "创建失败", "无法创建该文件！", QMessageBox::NoButton);
            return;
        }
        file.close();
        QTreeWidgetItem* parent = nullptr;
        if(fileInfo.isFile()){
            parent = item->parent();
        }else{
            parent = item;
        }
        CodeTreeWidgetItem* newChild = addChildFileItem(path, dynamic_cast<CodeTreeWidgetItem*>(parent));
        // 重命名
        this->startEditTreeItem(newChild, 0);

    }else if(text =="创建文件夹"){
        // 创建文件夹
        QFileInfo fileInfo(filePath);
        QString path;
        QDir dir;
        QString newName;
        if(fileInfo.isFile()){
            dir = fileInfo.absoluteDir();
            newName = genFileSoleName(dir, this->defaultDirName);
        }else if(fileInfo.isDir()){
            dir.setPath(filePath);
            newName = genFileSoleName(dir, this->defaultDirName);
        }
        if(newName.isEmpty()){
            QMessageBox::warning(this, "创建失败", "文件夹名生成失败！", QMessageBox::NoButton);
            return;
        }else{
            if(!dir.mkdir(newName)){
                QMessageBox::warning(this, "创建失败", "无法创建该文件夹！"+newName, QMessageBox::NoButton);
                return;
            }
        }
        path = dir.filePath(newName);
        //更新UI显示
        QTreeWidgetItem* parent = nullptr;
        if(fileInfo.isFile()){
            parent = item->parent();
        }else{
            parent = item;
        }
        CodeTreeWidgetItem* newChild = addChildFileItem(path, dynamic_cast<CodeTreeWidgetItem*>(parent));
        // 重命名
        this->startEditTreeItem(newChild, 0);
    }else if(text =="重命名"){
        //item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
        this->startEditTreeItem(item_p, 0);

    }else if(text =="删除文件"){
        if(QFile::remove(filePath)){
            QTreeWidgetItem* parent = item->parent();
            if(parent){
                CodeTreeWidgetItem* parent_p = dynamic_cast<CodeTreeWidgetItem*>(parent);
                clearChildren(parent_p);
                QDir dir(parent_p->toolTip(0));
                this->loadChildFile(dir,parent_p);
            }
            GlobalData::editCodeManager->removeOpenedFile(filePath);
        }else{
            QMessageBox::critical(this, "删除失败", "无法删除该文件！\nfile: "+filePath, QMessageBox::NoButton);
        }
    }else if(text =="删除文件夹"){

    }
}

void CodeTreeSideWidget::_on_ProjectAdded(std::shared_ptr<Project> project)
{
    this->loadProjectFileTree(project);
}

void CodeTreeSideWidget::_on_ProjectRemoved(std::shared_ptr<Project> project)
{
    int size = this->treeWidget->topLevelItemCount();
    for(int i=0; i<size; i++){
        CodeTreeWidgetItem* item_p = dynamic_cast<CodeTreeWidgetItem*>(this->treeWidget->topLevelItem(i));
        if(item_p->project == project){
            this->treeWidget->takeTopLevelItem(i);
            SAFE_DELE_P(item_p);
            break;
        }
    }
}

void CodeTreeSideWidget::_on_nameEditingFinished()
{
    try {
        if (this->currentEditNameItem == nullptr){
            throw std::exception();
        }
        QLineEdit *edit = qobject_cast<QLineEdit*>(treeWidget->itemWidget(currentEditNameItem, 0));
        QString text = edit->text();
        QString oldText = currentEditNameItem->text(0);
        QString path = currentEditNameItem->toolTip(0);
        QFileInfo fileInfo(path);
        QDir dir = fileInfo.absoluteDir();
        if(oldText != text){
            if(!QFile::rename(path, dir.filePath(text))){
                QMessageBox::critical(this, "重命名失败", "无法更改该文件名称！\nfile: "+path, QMessageBox::NoButton);
                throw std::exception();
            }
            currentEditNameItem->setText(0, text);
            GlobalData::editCodeManager->setFileName(path, text);
        }

    } catch (std::exception e) {

    }
    treeWidget->removeItemWidget(currentEditNameItem, 0);
}


CodeTreeWidgetItem::CodeTreeWidgetItem(QTreeWidgetItem *parent)
    : QTreeWidgetItem(parent)
{

}
