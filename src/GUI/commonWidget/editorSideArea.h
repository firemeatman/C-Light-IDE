
#ifndef EDITORSIDEAREA_H
#define EDITORSIDEAREA_H


#include <QWidget>
#include <QTextBlock>
#include <QPlainTextEdit>

class EditorSideArea : public QWidget
{

public:
    EditorSideArea(QWidget* parent = nullptr);

    int lineNumberAreaWidth() const;
    void lineNumberAreaPaintEvent(QPaintEvent* event);
    //int blockCount() const;

    QSize sizeHint() const override
    {
        return QSize(lineNumberAreaWidth(), 0);
    }

    QPlainTextEdit* boundingTextEdit;



protected:
    void paintEvent(QPaintEvent *event) override
    {
        lineNumberAreaPaintEvent(event);
    }
};


#endif // EDITORSIDEAREA_H
