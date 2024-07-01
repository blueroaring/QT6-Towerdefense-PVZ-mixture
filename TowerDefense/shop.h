#ifndef SHOP_H
#define SHOP_H
#include<QGraphicsItem>
#include<QPainter>
class Shop : public QGraphicsItem//生成选卡界面（卡片单独在shopcard类）
{
public:
    Shop();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int playerhp;//玩家基地生命
};


#endif // SHOP_H
