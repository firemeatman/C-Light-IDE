#ifndef CODEPAGE_H
#define CODEPAGE_H

#include <QMainWindow>
#include <QDockWidget>
#include "codeTreeSideWidget.h"
#include "codeFileListWidget.h"
#include "codePageEditWidget.h"

class CodePage : public QMainWindow
{
    Q_OBJECT
public:
    explicit CodePage(QWidget *parent = nullptr);

    CodePageEditWidget* codePageEditWidget = nullptr;
    CodeTreeSideWidget* codeTreeSideWidget = nullptr;
    CodeFileListWidget* codeFileListWidget = nullptr;
    QDockWidget* codeTreeSidedockWidget = nullptr;
    QDockWidget* codeFileListdockWidget = nullptr;

signals:
};

#endif // CODEPAGE_H
