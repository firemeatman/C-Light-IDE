
#ifndef EDITORSIDEAREA_H
#define EDITORSIDEAREA_H


#include <QWidget>
#include <QTextBlock>
#include <QPlainTextEdit>

class EditorSideArea : public QWidget
{

public:
    EditorSideArea(QWidget* parent = nullptr);


    void lineNumberAreaPaintEvent(QPaintEvent* event);

    QSize sizeHint() const override;

    QPlainTextEdit* boundingTextEdit;



protected:
    void paintEvent(QPaintEvent *event) override
    {
        lineNumberAreaPaintEvent(event);
    }
};


#endif // EDITORSIDEAREA_H
