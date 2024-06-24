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
    this->closeProjectAction = new QAction(tr("关闭项目"), this);
    this->newFileAction = new QAction(tr("新文件"), this);
    this->newFloderAction = new QAction(tr("创建文件夹"), this);
    this->renameAction = new QAction(tr("重命名"), this);
    this->deleFileAction = new QAction(tr("删除文件"), this);
    this->deleFloderAction = new QAction(tr("删除文件夹"), this);

    fileMenu->addAction(closeProjectAction); // 0
    fileMenu->addAction(newFileAction); // 1
    addfileMenu = new QMenu(tr("创建更多文件"),this);
    addfileMenu->addAction("空白文件");
    addfileMenu->addAction(".h文件");
    addfileMenu->addAction(".c文件");
    addfileMenu->addAction(".cpp文件");
    addfileMenu->addAction("c++类");
    fileMenu->addMenu(addfileMenu);
    fileMenu->addAction(newFloderAction);
    fileMenu->addAction(renameAction);
    fileMenu->addAction(deleFileAction);
    fileMenu->addAction(deleFloderAction);

    connect(this->treeWidget, &QTreeWidget::itemDoubleClicked, this, &CodeTreeSideWidget::_on_itemDoubleCliced);
    connect(this->treeWidget, &QTreeWidget::itemPressed, this, &CodeTreeSideWidget::_on_itemPressed);
    connect(GlobalData::projectManager, &ProjectManager::projectAdded, this, &CodeTreeSideWidget::_on_ProjectAdded);
    connect(GlobalData::projectManager, &ProjectManager::projectRemoved, this, &CodeTreeSideWidget::_on_ProjectRemoved);

    connect(closeProjectAction, &QAction::triggered, this, &CodeTreeSideWidget::_on_closeProjectActionTriggered);
    connect(newFileAction, &QAction::triggered, this, &CodeTreeSideWidget::_on_newFileActionTriggered);
    connect(newFloderAction, &QAction::triggered, this, &CodeTreeSideWidget::_on_newFloderActionTriggered);
    connect(renameAction, &QAction::triggered, this, &CodeTreeSideWidget::_on_renameActionTriggered);
    connect(deleFileAction, &QAction::triggered, this, &CodeTreeSideWidget::_on_deleFileActionTriggered);
    connect(deleFloderAction, &QAction::triggered, this, &CodeTreeSideWidget::_on_deleFloderActionTriggered);

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
        if(action == this->closeProjectAction){
            if(!(type & SelectItemType::ProjectRoot)){
                action->setVisible(false);
            }
        }else if(action == this->renameAction){
            if(type & SelectItemType::ProjectRoot || type & SelectItemType::Dir){
                action->setVisible(false);
            }
        }else if(action == this->deleFileAction){
            if(type & SelectItemType::ProjectRoot || type & SelectItemType::Dir){
                action->setVisible(false);
            }
        }else if(action == this->deleFileAction){
            if(type & SelectItemType::ProjectRoot || type & SelectItemType::File){
                action->setVisible(false);
            }
        }
    }

    fileMenu->exec(QCursor::pos());
}


void CodeTreeSideWidget::_on_closeProjectActionTriggered(bool isChecked)
{
    QTreeWidgetItem* item = this->treeWidget->currentItem();
    if(!item) return;
    CodeTreeWidgetItem* item_p = dynamic_cast<CodeTreeWidgetItem*>(item);

    std::shared_ptr<Project> project = item_p->project;
    if(project){
        GlobalData::projectManager->removeProject(project);
    }
}

void CodeTreeSideWidget::_on_newFileActionTriggered(bool isChecked)
{
    QTreeWidgetItem* item = this->treeWidget->currentItem();
    if(!item) return;
    QString filePath = item->toolTip(0);

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

}

void CodeTreeSideWidget::_on_newFloderActionTriggered(bool isChecked)
{
    QTreeWidgetItem* item = this->treeWidget->currentItem();
    if(!item) return;
    QString filePath = item->toolTip(0);

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
}

void CodeTreeSideWidget::_on_renameActionTriggered(bool isChecked)
{
    QTreeWidgetItem* item = this->treeWidget->currentItem();
    if(!item) return;
    CodeTreeWidgetItem* item_p = dynamic_cast<CodeTreeWidgetItem*>(item);

    //item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
    this->startEditTreeItem(item_p, 0);
}

void CodeTreeSideWidget::_on_deleFileActionTriggered(bool isChecked)
{
    QTreeWidgetItem* item = this->treeWidget->currentItem();
    if(!item) return;
    QString filePath = item->toolTip(0);

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
}

void CodeTreeSideWidget::_on_deleFloderActionTriggered(bool isChecked)
{
    QTreeWidgetItem* item = this->treeWidget->currentItem();
    if(!item) return;
    QString filePath = item->toolTip(0);

    QDir dir(filePath);
    if(dir.isEmpty()){
        dir.removeRecursively();
        QTreeWidgetItem* parent = item->parent();
        if(parent){
            CodeTreeWidgetItem* parent_p = dynamic_cast<CodeTreeWidgetItem*>(parent);
            clearChildren(parent_p);
            QDir dir(parent_p->toolTip(0));
            this->loadChildFile(dir,parent_p);
        }
    }else{
        QMessageBox::critical(this, "删除失败", "该文件夹不为空！\nfile: "+filePath, QMessageBox::NoButton);
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
