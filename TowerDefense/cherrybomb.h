#ifndef CHERRYBOMB_H
#define CHERRYBOMB_H
#include"tower.h"
#include<QTimer>
//樱桃炸弹
class CherryBomb: public Tower
{
public:
    CherryBomb();
    CherryBomb(QPointF point);

    QRectF boundingRect() const;//实际上没用到
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
private:
    int prepareTime, counter;//爆炸前准备时间
    bool atkStatus;//攻击状态（是不是要爆了）

};

#endif // CHERRYBOMB_H
