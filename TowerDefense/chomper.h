#ifndef CHOMPER_H
#define CHOMPER_H
#include"tower.h"
#include"enemy.h"
#include<QTimer>
#include<QGraphicsSceneMouseEvent>
//大嘴花
class Chomper:public Tower
{
public:
    Chomper();
    Chomper(QPointF point);
    void advance(int phase)override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode)  const override;

private:
    int setStatus, nowStatus;

};

#endif // CHOMPER_H
