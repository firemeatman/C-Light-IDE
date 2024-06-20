#include "codePage.h"

#include "../../../common/global_data.h"
CodePage::CodePage(QWidget *parent)
    : QMainWindow{parent}
{
    codeTreeSideWidget = new CodeTreeSideWidget(this);
    codePageEditWidget = new CodePageEditWidget(this);
    codeFileListWidget = new CodeFileListWidget(this);

    codeTreeSidedockWidget = new QDockWidget(this);
    codeFileListdockWidget = new QDockWidget(this);
    this->setCentralWidget(codePageEditWidget);
    codePageEditWidget->show();

    codeTreeSidedockWidget->setWidget(codeTreeSideWidget);
    codeTreeSidedockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    codeFileListdockWidget->setWidget(codeFileListWidget);
    codeFileListdockWidget->setFloating(false);

    this->addDockWidget(Qt::LeftDockWidgetArea, codeTreeSidedockWidget);
    this->addDockWidget(Qt::LeftDockWidgetArea, codeFileListdockWidget);
    codeTreeSidedockWidget->setMinimumWidth(150);
    this->resize(500,500);
    int width = this->width();
    this->splitDockWidget(codeTreeSidedockWidget,codeFileListdockWidget,Qt::Horizontal);
    this->resizeDocks({codeTreeSidedockWidget,codeFileListdockWidget}, {static_cast<int>(width*0.5), static_cast<int>(width*0.5)}, Qt::Horizontal);

    codeFileListdockWidget->hide();
    //=======================信号===========================
    connect(GlobalData::editCodeManager, &EditCodeManager::fileOpened,this,&CodePage::_on_fileOpened);
}

void CodePage::_on_fileOpened(FileStruct file)
{
    codeFileListdockWidget->show();
}
