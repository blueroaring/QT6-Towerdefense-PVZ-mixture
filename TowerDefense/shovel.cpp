#include "shovel.h"
#include<QPainter>
#include<QMouseEvent>
#include<QGraphicsObject>
#include<QDrag>
#include<QMimeData>
#include<QApplication>
#include<QGraphicsSceneMouseEvent>
#include<QMediaPlayer>
#include<QAudioOutput>
shovel::shovel() :shovel_clicked(false),shovel_pos(QPoint(0,0)){

}
QRectF shovel::boundingRect() const
{
    return QRectF(1140, 150, 100, 50);
}

void shovel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
   // qDebug()<<"paintused";
    painter->drawPixmap(QRect(1140,150,100,50), QPixmap(":/new/Image/Images/Others/controller/menulist/showelsocket.png"));
    painter->drawPixmap(QRect(1140,150,100,50), QPixmap(":/new/Image/Images/Others/controller/menulist/showel.png"));

}

void shovel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    Q_UNUSED(event);
        qDebug()<<"used press";
        shovel_clicked=true;//传到mapway里
        QCursor cursor(QPixmap(":/new/Image/Images/Others/controller/menulist/showel.png"), 10, 10);
        // 设置光标
        this->setCursor(cursor);
        QMediaPlayer *win=new QMediaPlayer;
        QAudioOutput *Win=new QAudioOutput;
        win->setAudioOutput(Win);
        win->setSource(QUrl("../Music/shovel.mp3"));
        Win->setVolume(50);
        win->setLoops(QMediaPlayer::Once);
        win->play();

}

