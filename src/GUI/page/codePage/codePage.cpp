#include "codePage.h"

CodePage::CodePage(QWidget *parent)
    : QMainWindow{parent}
{
    codePageEditWidget = new CodePageEditWidget(this);
    codeTreeSideWidget = new CodeTreeSideWidget(this);
    codeFileListWidget = new CodeFileListWidget(this);
    codeTreeSidedockWidget = new QDockWidget(this);
    codeFileListdockWidget = new QDockWidget(this);
    this->setCentralWidget(codePageEditWidget);

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
}
