
#ifndef TERMINALWIDGET_H
#define TERMINALWIDGET_H


#include <QWidget>
#include <QPlainTextEdit>

class TerminalWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TerminalWidget(QWidget *parent = nullptr);
    ~TerminalWidget();

    void addMsg(QString& str);
    void setMsg(QString& str);
    void clearMsg(QString& str);

public:
    //QString recvedMsg;
    QPlainTextEdit* plainTextEdit;

};

#endif // TERMINALWIDGET_H
