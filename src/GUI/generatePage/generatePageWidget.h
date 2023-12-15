#ifndef GENERATEPAGEWIDGET_H
#define GENERATEPAGEWIDGET_H

#include <QWidget>

namespace Ui {
class GeneratePageWidget;
}

class GeneratePageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GeneratePageWidget(QWidget *parent = nullptr);
    ~GeneratePageWidget();

private:
    Ui::GeneratePageWidget *ui;

public slots:
    void _on_clicked_complierSelectBtn();
    void _on_clicked_makeSelectBtn();
    void _on_clicked_debugerSelectBtn();
    void _on_clicked_makefileSelectBtn();
};

#endif // GENERATEPAGEWIDGET_H
