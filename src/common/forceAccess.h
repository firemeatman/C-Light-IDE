
#ifndef FORCEACCESS_H
#define FORCEACCESS_H


#include <QPlainTextEdit>
#include <QTextBlock>
class ForceAccess
{
public:
    ForceAccess();

public:
    class ForceQPlainText : public QPlainTextEdit{
    public:
        QTextBlock firstVisibleBlock(){
            return  QPlainTextEdit::firstVisibleBlock();
        }
        QRectF blockBoundingGeometry(QTextBlock& block){
            return QPlainTextEdit::blockBoundingGeometry(block);
        }
        QPointF contentOffset() const{
            return QPlainTextEdit::contentOffset();
        }
        QRectF blockBoundingRect(QTextBlock& block){
            return QPlainTextEdit::blockBoundingRect(block);
        }
        //blockBoundingRect

    };

};




#endif // FORCEACCESS_H
