#ifndef PEA_H
#define PEA_H
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include <QPointF>
#include <QDebug>
#include <QTime>

class Pea : public QGraphicsItem
{
public:
    enum { Type = UserType + 3};//用于碰撞箱判定
    Pea(QPointF point,int ty, bool _isSnow=false);//带默认参数的构造函数
    ~Pea();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
    int type() const;//返回类型
    int buttaltype;//子弹类型，0：右，1，左，2，下，3，上
    bool bump;//是否击中敌人
   float ATK;//攻击
    bool slower;//是否有晕眩词缀
   bool isdelete;//是否delete
    bool hasbomb;//是否拥有狂暴
private:
    int posX, posY;//坐标

    bool isSnow;//是雪球
};


#endif // PEA_H

