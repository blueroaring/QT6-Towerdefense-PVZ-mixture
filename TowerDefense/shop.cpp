#include "shop.h"
Shop::Shop()
{
    setZValue(0);
    playerhp=5;

}

QRectF Shop::boundingRect() const
{
    return QRectF(0, 0, 1140, 200);
}

void Shop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(200, 0, 940, 200), QPixmap(":/new/Image/Images/Others/controller/Shop.png"));
    painter->setFont(QFont("Arial", 15));
    painter->drawText(0, 50, "当前基地血量："+QString::number(playerhp));

}

