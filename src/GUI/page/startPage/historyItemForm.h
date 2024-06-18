#ifndef HISTORYITEMFORM_H
#define HISTORYITEMFORM_H

#include <QWidget>
#include "../../../model/modelDataDef.h"
namespace Ui {
class HistoryItemForm;
}

class HistoryItemForm : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryItemForm(QWidget *parent = nullptr);
    ~HistoryItemForm();

    QString name;
    QString path;

    void setData(HistoryProject& data);

private:
    Ui::HistoryItemForm *ui;
};

#endif // HISTORYITEMFORM_H
