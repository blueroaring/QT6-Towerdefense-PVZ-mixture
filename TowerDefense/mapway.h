#ifndef MAPWAY_H
#define MAPWAY_H
#include<QPainter>
#include<QMap>
#include"tower.h"
#include"shovel.h"
#include"shopcard.h"
#include"shop.h"
#include "enemy.h"
#include "cherrybomb.h"
#include"words.h"
class mapway:public QGraphicsItem
{
public:
    mapway();
    friend class game;
    ~mapway();
    void advance(int phase) override;//更新
    //这三个都是种卡的
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;//点击地图事件
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;//光标悬浮事件
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;//鼠标松开事件
    Tower *plantmap[8][13];//种植物数组
    QGraphicsScene *scene;//link scene
    shopcard* Shopcard;
    Words *words;
    bool ispause;//暂停
    int mapArr[8][13];//地图数组
private:

    QRectF boundingRect() const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QMap<int,QString> map_value_to_path;//存对应区块格图片
    bool dragOver;//被拖动，因为后来拖动被移除了（bug太多）,现在没有用了
    shovel *Shovel;//集成铲子
    shopcard *PreparedPlant;//准备好种的植物
};

#endif // MAPWAY_H
