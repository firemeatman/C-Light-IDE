#ifndef MAKECONFIGWIDGET_H
#define MAKECONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class MakeConfigWidget;
}

class MakeConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MakeConfigWidget(QWidget *parent = nullptr);
    ~MakeConfigWidget();

private:
    Ui::MakeConfigWidget *ui;
public slots:
    void _on_clicked_complierSelectBtn();
    void _on_clicked_makeExeSelectBtn();
    void _on_clicked_mainMakefileSelectBtn();
    void _on_clicked_targetExeDirSelectBtn();
    void _on_clicked_targetExeNameSelectBtn();

};

#endif // MAKECONFIGWIDGET_H
