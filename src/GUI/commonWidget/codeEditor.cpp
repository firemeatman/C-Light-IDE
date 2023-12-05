
#include "codeEditor.h"
#include <QPainter>

#include <QTextFormat>
CodeEditor::CodeEditor(QWidget *parent)
    : QPlainTextEdit(parent)
{
    editorSideArea = new EditorSideArea(this);
    editorSideArea->boundingTextEdit = this;
    editorSideArea->show();
    editorSideArea->setUpdatesEnabled(true);

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();


}

int CodeEditor::lineNumberAreaWidth() const
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
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
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::highlightCurrentLine()
{
//    QList<QTextEdit::ExtraSelection> selections = extraSelections();
//    QTextCharFormat textCharFormat;
//    QFont font("Times", 15);
//    textCharFormat.setFont(font);
//    for(int i=0;i<selections.size();i++){
//        selections[i].format = textCharFormat;
//    }
    QList<QTextEdit::ExtraSelection> selections;

    QTextCharFormat textCharFormat;
    QFont font("Times", 15);
    QBrush brush(Qt::SolidPattern);
    brush.setColor(Qt::GlobalColor::blue);
    textCharFormat.setFont(font);
    textCharFormat.setBackground(brush);

    QTextCursor currentTextCursor = textCursor();
    QTextBlock currentCursorBlock = currentTextCursor.block();
    QTextCursor beginCursor(currentCursorBlock);
    int pos= beginCursor.position();
    while(1){

        QTextCursor cursor(currentCursorBlock);
        cursor.setPosition(pos);
        pos++;
        QTextEdit::ExtraSelection selection;
        selection.cursor = cursor;
        selection.format = textCharFormat;
        selections.append(selection);
        if(cursor.atBlockEnd()){
            break;
        }
    }

    setExtraSelections(selections);
}

