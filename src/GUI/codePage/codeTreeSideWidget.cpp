#include "codeTreeSideWidget.h"
#include "ui_codeTreeSideWidget.h"

#include <QPushButton>
#include <QTreeWidget>



CodeTreeSideWidget::CodeTreeSideWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodeTreeSideWidget)
{
    treeMenu = new TreeMenu(this);
    //treeMenu->hide();
    //ui->setupUi(this);
    //connect(ui->pushButton, &QPushButton::clicked, this, &CodeTreeSideWidget::_on_clicked_openDirBtn);

}

CodeTreeSideWidget::~CodeTreeSideWidget()
{
    delete ui;
}

void CodeTreeSideWidget::switchState(CodeSideWidgetState state)
{
    if(state == EMPUTY){
        treeMenu->hide();
        ui->widget->show();

    }else if(state == CodeTreeSideWidget::OPEN_DIR){
        if(!treeMenu){
            treeMenu = new TreeMenu(this);
        }
        ui->widget->hide();
        treeMenu->show();
    }
}

void CodeTreeSideWidget::_on_clicked_openDirBtn()
{
    if(current_state != CodeTreeSideWidget::OPEN_DIR){
        switchState(CodeTreeSideWidget::OPEN_DIR);
    }

}
