#ifndef WORDS_H
#define WORDS_H
#include<QGraphicsItem>
#include<QGraphicsSceneMouseEvent>
#include<QCursor>
#include<QPainter>
class Words: public QGraphicsItem
{
public:
    Words();
    int wordamount[5];//各个词缀的数量
    const static QVector<QString> name;//词缀名称，存档用

     void advance(int phase) override;
    QGraphicsScene *scene;//link scene
     QRectF boundingRect() const override;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
     void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
     bool ispause;//暂停
     bool ready;//已经准备释放词缀
     int prepared;//准备的词缀

};

#endif // WORDS_H
