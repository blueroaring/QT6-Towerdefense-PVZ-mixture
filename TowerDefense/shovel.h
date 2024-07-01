#ifndef SHOVEL_H
#define SHOVEL_H
#include "tower.h"
//铲子
class shovel: public QGraphicsItem
{
public:
    shovel();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;//点击铲子
   // void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
   // void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void removePlant(QPointF pos);//铲植物
    bool shovel_clicked;//是否点击过
    QPointF shovel_pos;//移动后的位置

private:

};

#endif // SHOVEL_H
