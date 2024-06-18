#include "codeTreeSideWidget.h"
#include "ui_codeTreeSideWidget.h"

#include <QPushButton>
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

    ui->verticalLayout->addWidget(treeWidget);
    ui->widget->hide();
    ui->pushButton->setFixedSize(80,30);

    connect(this->treeWidget, &QTreeWidget::itemDoubleClicked, this, &CodeTreeSideWidget::_on_itemDoubleCliced);
    connect(this->treeWidget, &QTreeWidget::itemPressed, this, &CodeTreeSideWidget::_on_itemPressed);
    connect(GlobalData::projectManager, &ProjectManager::projectAdded, this, &CodeTreeSideWidget::_on_ProjectAdded);

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
    if(qApp->mouseButtons() == Qt::RightButton){

    }
}

void CodeTreeSideWidget::_on_ProjectAdded(std::shared_ptr<Project> project)
{
    this->loadProjectFileTree(*project);
}
