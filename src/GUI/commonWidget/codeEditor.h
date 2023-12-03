
#ifndef CODEEDITOR_H
#define CODEEDITOR_H


#include <QWidget>
#include <QPlainTextEdit>
#include "editorSideArea.h"

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    CodeEditor(QWidget *parent= nullptr);


public slots:
    void updateLineNumberArea(const QRect &rect, int dy);
    void updateLineNumberAreaWidth(int /* newBlockCount */);
    void highlightCurrentLine();

private:
    EditorSideArea* editorSideArea;

};



#endif // CODEEDITOR_H
