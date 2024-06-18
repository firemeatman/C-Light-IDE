#include "codeTreeSideWidget.h"
#include "ui_codeTreeSideWidget.h"

#include <QVBoxLayout>
#include <QHeaderView>

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
    treeWidget->setAnimated(true); //展开折叠动画

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(treeWidget);

    // 菜单设置
    treeRootMenu = new QMenu(this);
    treeRootMenu->addAction("关闭项目");

    fileMenu = new QMenu(this);
    addfileMenu = new QMenu("创建文件",this);
    addfileMenu->addAction(".h文件");
    addfileMenu->addAction(".c文件");
    addfileMenu->addAction(".cpp文件");
    addfileMenu->addAction("c++类");
    fileMenu->addMenu(addfileMenu);

    connect(this->treeWidget, &QTreeWidget::itemDoubleClicked, this, &CodeTreeSideWidget::_on_itemDoubleCliced);
    connect(this->treeWidget, &QTreeWidget::itemPressed, this, &CodeTreeSideWidget::_on_itemPressed);
    connect(GlobalData::projectManager, &ProjectManager::projectAdded, this, &CodeTreeSideWidget::_on_ProjectAdded);

    connect(treeRootMenu, &QMenu::triggered, this, &CodeTreeSideWidget::_on_rootMenuTriggered);
    connect(fileMenu, &QMenu::triggered, this, &CodeTreeSideWidget::_on_fileMenuTriggered);

}

CodeTreeSideWidget::~CodeTreeSideWidget()
{
    delete ui;
}

void CodeTreeSideWidget::loadProjectFileTree(Project& project)
{
    QTreeWidgetItem* rootItem = new QTreeWidgetItem();
    this->treeWidget->addTopLevelItem(rootItem);

    rootItem->setText(0,project.name);
    rootItem->setIcon(0,QIcon(":/icons/resource/icons/file.png"));
    rootItem->setToolTip(0, project.projectRootDir);
    rootItem->setExpanded(true);

    QDir dir(project.projectRootDir);
    loadChildFile(dir, rootItem);
}

void CodeTreeSideWidget::loadChildFile(QDir &parentDir, QTreeWidgetItem *parent)
{
    QApplication::processEvents(); //防止界面假死
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
        QTreeWidgetItem *child = new QTreeWidgetItem(parent);
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

void CodeTreeSideWidget::_on_itemDoubleCliced(QTreeWidgetItem *item)
{

    QFileInfo fileInfo(item->toolTip(0));
    if(fileInfo.isDir()){
        int count = item->childCount();
        for(int i=count-1; i>=0; i--)
        {
            QTreeWidgetItem *childItem = item->child(i);//删除子节点
            item->removeChild(childItem);
            SAFE_DELE_P(childItem);
        }
        QDir dir(fileInfo.absoluteFilePath());
        loadChildFile(dir, item);
    }else if(fileInfo.isFile()){

    }
}

void CodeTreeSideWidget::_on_itemPressed(QTreeWidgetItem *item, int column)
{
    if(qApp->mouseButtons() != Qt::RightButton){
        return;
    }

    if(item->parent() == nullptr){
        treeRootMenu->exec(QCursor::pos());
    }else{
        fileMenu->exec(QCursor::pos());
    }
}

void CodeTreeSideWidget::_on_rootMenuTriggered(QAction *action)
{
    if(action->text() == "关闭项目"){
        QTreeWidgetItem* item = this->treeWidget->currentItem();
        QString path = item->toolTip(0);
        std::shared_ptr<Project> project = GlobalData::projectManager->findProject(path);
        if(project){
            GlobalData::projectManager->removeProject(project);
            int index = this->treeWidget->indexOfTopLevelItem(item);
            if(index >= 0){
                this->treeWidget->takeTopLevelItem(index);
                SAFE_DELE_P(item);
            }
        }
    }
}

void CodeTreeSideWidget::_on_fileMenuTriggered(QAction *action)
{
    if(action->text() == ".h文件"){

    }
}

void CodeTreeSideWidget::_on_ProjectAdded(std::shared_ptr<Project> project)
{
    this->loadProjectFileTree(*project);
}

