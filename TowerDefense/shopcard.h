#ifndef SHOPCARD_H
#define SHOPCARD_H
#include<QGraphicsItem>
#include<QGraphicsSimpleTextItem>
#include<QGraphicsScene>
//卡槽
class shopcard: public QGraphicsItem
{
public:

    shopcard();
    ~shopcard();
    const static QMap<QString, int> map;//键值对
    const static QVector<QString> name;//卡槽植物名称
    const static QVector<int> cost;//卡槽植物花费
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;//点击卡槽
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;//释放鼠标
    int NO;//判断植物类型
    bool ispause;//暂停
    bool readyPlanted;//准备种植
    int  sunNeed, counter;//种这个植物需要的阳光，计数器
    int sunTotal;//阳光总数
    int hex;//用于setcursor

    QGraphicsScene *scene;
    void advance(int phase) override;
protected:

};
#endif
