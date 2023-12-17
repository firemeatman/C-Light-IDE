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

    typedef enum{
        SysInfoMsg = 0,
        ExternInfoMsg,
        SysErrorMsg,
    } MsgType;

    explicit MakeInfoWidget(QWidget *parent = nullptr);
    ~MakeInfoWidget();

    QPlainTextEdit* plainTextEdit = nullptr;

    void addStr(QString &str, MsgType type);

private:
    Ui::makeInfoWidget *ui;

    QTextCharFormat NormalTextFormat;
    QTextCharFormat ErrorTextFormat;
    QTextCharFormat SystemTextFormat;


public slots:
    void addMsg(QString &str);
    void _on_cleanButton_clicked(bool is_checked);
    void _cleanCompleted(QString &taskName, int code, QString &info);
};

#endif // MAKEINFOWIDGET_H
