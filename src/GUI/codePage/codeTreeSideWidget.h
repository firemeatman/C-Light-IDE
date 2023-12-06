#ifndef CODETREESIDEWIDGET_H
#define CODETREESIDEWIDGET_H

#include <QWidget>
#include "../../third/TreeMenu.h"
namespace Ui {
class CodeTreeSideWidget;
}

class CodeTreeSideWidget : public QWidget
{
    Q_OBJECT

public:
    typedef enum{
        EMPUTY,
        OPEN_DIR,
    } CodeSideWidgetState;


public:
    explicit CodeTreeSideWidget(QWidget *parent = nullptr);
    ~CodeTreeSideWidget();

    void switchState(CodeTreeSideWidget::CodeSideWidgetState state);

    CodeSideWidgetState current_state = EMPUTY;


    TreeMenu *getTreeMenu() const;

private:
    Ui::CodeTreeSideWidget *ui;

    TreeMenu* treeMenu = nullptr;



protected slots:
    void _on_clicked_openDirBtn();
};

#endif // CODETREESIDEWIDGET_H
