#ifndef REPEATER_H
#define REPEATER_H
#include"tower.h"
#include"pea.h"
#include"enemy.h"
#include<QGraphicsSceneMouseEvent>
//双发射手
class repeater: public Tower
{
public:
    repeater();
    repeater(QPointF pos);
    ~repeater();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;

private:
    Pea *pea;
    int peaCounter, peaCreateTime;
};

#endif // REPEATER_H
