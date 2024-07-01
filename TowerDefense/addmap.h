#ifndef ADDMAP_H
#define ADDMAP_H
#include<QGraphicsItem>
class addmap: public QGraphicsItem
{
public:
    addmap();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
private:
    bool dragOver;
};

#endif // ADDMAP_H
