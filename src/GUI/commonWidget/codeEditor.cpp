
#include "codeEditor.h"
#include <QPainter>


CodeEditor::CodeEditor(QWidget *parent)
    : QPlainTextEdit(parent)
{
    editorSideArea = new EditorSideArea(this);
    editorSideArea->boundingTextEdit = this;
    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();


}




void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        dynamic_cast<QWidget*>(editorSideArea)->scroll(0 , dy);
    else
        dynamic_cast<QWidget*>(editorSideArea)->update(0, rect.y(), dynamic_cast<QWidget*>(editorSideArea)->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEditor::updateLineNumberAreaWidth(int)
{
    setViewportMargins(editorSideArea->lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::highlightCurrentLine()
{

}

