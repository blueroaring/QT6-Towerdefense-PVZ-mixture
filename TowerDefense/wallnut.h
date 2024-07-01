#ifndef WALLNUT_H
#define WALLNUT_H
#include"tower.h"
#include<QGraphicsSceneMouseEvent>
//坚果墙
class Wallnut:public Tower
{
public:
    Wallnut();
    Wallnut(QPointF point);
    ~Wallnut();
    void advance(int phase) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;



private:
    int setStatus, nowStatus;
    int maxhp;

};

#endif // WALLNUT_H
