#ifndef MAKEINFOWIDGET_H
#define MAKEINFOWIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
namespace Ui {
class makeInfoWidget;
}

class MakeInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MakeInfoWidget(QWidget *parent = nullptr);
    ~MakeInfoWidget();

    QPlainTextEdit* plainTextEdit = nullptr;

private:
    Ui::makeInfoWidget *ui;

public slots:
    void addMsg(QString &str);
};

#endif // MAKEINFOWIDGET_H
