#ifndef CALTROP_H
#define CALTROP_H
#include"tower.h"
#include"enemy.h"
#include<QGraphicsSceneMouseEvent>
//地刺
class Caltrop:public Tower
{
public://其它的近战植物类似，重复的地方不再注释
    Caltrop();
    Caltrop(QPointF point);//使用的种植的构造函数
    void advance(int phase);//更新实时状态
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);//更新绘制
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;//碰撞箱

private:
    int setStatus, nowStatus;//状态控制
};

#endif // CALTROP_H
