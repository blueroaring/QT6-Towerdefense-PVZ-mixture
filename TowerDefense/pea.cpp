#include "pea.h"
#include"enemy.h"
#include<QMediaPlayer>
#include<QAudioOutput>
Pea::Pea(QPointF point, int ty,bool _isSnow):isSnow(_isSnow),buttaltype(ty)
{
    bump=0;
    if(isSnow){
        ATK=5;
    }
    else
    ATK = 10;
    posX = point.x();
    posY = point.y();
    //qDebug()<<posX<<posY;
    setPos(0, 0);
    setZValue((posY-50)/90);
    slower=false;
    isdelete=0;
    hasbomb=0;
}

Pea::~Pea()
{

}

QRectF Pea::boundingRect() const
{
    return QRectF(0, 0, 150, 150);
}

void Pea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(!bump){
    if(!isSnow)
        {
            painter->drawImage(QRectF(posX,posY,30,30), QImage(":/cards/Images/Others/FirePea/PeaNormal_0.png"));}
    if(isSnow)
        painter->drawImage(QRectF(posX,posY,30,30), QImage(":/cards/Images/Others/FirePea/PeaIce_0.png"));
    }

    if(isdelete)
       painter->drawImage(QRectF(posX,posY,30,30), QImage(":/cards/Images/Others/FirePea/PeaNormalExplode_0.png"));

}

void Pea::advance(int phase)
{//右左下上
    switch(buttaltype){
    case 0:
        posX+=5;break;
    case 1:
        posX-=5;break;
    case 2:
        posY+=5;break;
    case 3:
        posY-=5;break;
    default:
        break;
    }
    if(posX<200||posX>1200||posY<200||posY>1000)
    {delete this;
        return;}
    update();
    int i=0;
    if(!phase)
        return;
    update();
    QList <QGraphicsItem *> items = collidingItems();
    if(!items.isEmpty())
    {
        foreach (QGraphicsItem *item, items)
        {
            Enemy *zombie = qgraphicsitem_cast<Enemy *>(item);
            if(zombie->posX-posX>-120&&zombie->posX-posX<10&&zombie->posY-posY>-90&&zombie->posY-posY<30&&i==0){
                zombie->nowHP -= ATK;
                i++;
                if(!isSnow&&slower&&zombie->speedFactor>60&&!zombie->hasrefresh)
                {zombie->speedFactor = 60;
                    zombie->Factor=0.6;

                    zombie->update();}
                if(isSnow&&slower&&!zombie->hasrefresh){
                    zombie->speedFactor=0;
                    zombie->Factor=0;
                    zombie->update();
                }
                if(isSnow&&!slower&&zombie->speedFactor>40&&!zombie->hasrefresh){
                    zombie->speedFactor=40;
                    zombie->Factor=0.4;
                    zombie->update();
                }
                bump=1;
                isdelete=1;
                update();

                    QMediaPlayer *win=new QMediaPlayer;
                    QAudioOutput *Win=new QAudioOutput;
                    win->setAudioOutput(Win);
                    if(isSnow)
                    win->setSource(QUrl("../Music/frozen.mp3"));
                  /*  else
                        win->setSource(QUrl("../Music/splat.mp3"));*/
                    Win->setVolume(50);
                    win->setLoops(QMediaPlayer::Once);
                    win->play();

                    delete this;
            }
        }




    }

    if(posX<200||posX>1200||posY<200||posY>900){
        delete this;
    }
}

bool Pea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    return other->type() == Enemy::Type ;
}

int Pea::type() const
{
    return Type;
}
