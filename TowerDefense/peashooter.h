#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include"tower.h"
#include"pea.h"
#include"enemy.h"
#include<QGraphicsSceneMouseEvent>
//豌豆射手
class PeaShooter:public Tower
{
public:
    PeaShooter();
    PeaShooter(QPointF point);//构造函数
    ~PeaShooter();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;

private:
    Pea *pea;//子弹
    int peaCounter, peaCreateTime;//控制子弹发射间隔
};

#endif // PEASHOOTER_H
