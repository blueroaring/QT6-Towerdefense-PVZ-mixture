#include "cherrybomb.h"
#include"enemy.h"
#include<QMediaPlayer>
#include<QAudioOutPut>
CherryBomb::CherryBomb(QPointF point)
{
    state=4;
    oldHP = 1500; atk = 1800; prepareTime = 50; counter = 0;
    hp=oldHP;
    atkStatus = 0;
    movie = new QMovie(":/shopcard/Images/Plants/CherryBomb/explode.gif");
    movie->setSpeed(25);
    movie->start();
    posX = point.x();
    posY = point.y()+25;
    setPos(posX, posY);
    name="Cherrybomb";

}

QRectF CherryBomb::boundingRect() const
{
    return QRectF(-50, -50, 300, 300);
}

void CherryBomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(!atkStatus)
        painter->drawImage(QRectF(0,0,120,120), movie->currentImage());
    else{
        painter->drawImage(QRectF(-30, -30, 200, 200), movie->currentImage());
        }
}

void CherryBomb::advance(int phase)
{
    if(!phase)
        return;
    update();
   // qDebug()<<"advance cherry";
    if(!atkStatus && counter >= prepareTime)
    {
        delete movie;
        movie = new QMovie(":/shopcard/Images/Plants/CherryBomb/Boom.gif");
        movie->start();
        atkStatus = 1;
    }
    if(atkStatus)
    {
        QMediaPlayer *win=new QMediaPlayer;
        QAudioOutput *Win=new QAudioOutput;
        win->setAudioOutput(Win);
        win->setSource(QUrl("../Music/cherrybomb.mp3"));
        Win->setVolume(50);
        win->setLoops(QMediaPlayer::Once);
        win->play();
       QList<QGraphicsItem *> items = collidingItems();
        foreach(QGraphicsItem *item, items)
        {
            Enemy *zombie = qgraphicsitem_cast<Enemy *>(item);
            if(zombie->posX-posX>-120&&zombie->posX-posX<120&&zombie->posY-posY>-120&&zombie->posY-posY<120&&!zombie->hasdisturb){
                zombie->nowHP -= atk;}

        }
        if(movie->currentFrameNumber() == movie->frameCount() - 1)
        {scene->removeItem(this);
            delete this;}
    }
    else
        counter+=3;
    if(hp <= 0){
        scene->removeItem(this);
        }
}

bool CherryBomb::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    Q_UNUSED(other);
    return other->type() == Enemy::Type;
}

