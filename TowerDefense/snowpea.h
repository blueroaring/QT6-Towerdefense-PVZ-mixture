#ifndef SNOWPEA_H
#define SNOWPEA_H
#include"tower.h"
#include"mapway.h"
#include"pea.h"
#include"enemy.h"
#include<QGraphicsSceneMouseEvent>
//寒冰射手
class SnowPea:public Tower
{
public:
    SnowPea(QPointF point);
   ~SnowPea();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;


private:
    Pea *pea;
    int peaCounter, peaCreateTime;

};

#endif // SNOWPEA_H
