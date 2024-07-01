#include "snowpea.h"
SnowPea::SnowPea(QPointF point)
{
    oldHP=300;
    hp = oldHP; peaCounter = 0; peaCreateTime = 42;
    movie = new QMovie(":/shopcard/Images/Plants/SnowPea/idle.gif");
    movie->start();
    posX = point.x();
    posY = point.y();
    setPos(posX, posY);
    state=2;
    name="Snowpea";
}

SnowPea::~SnowPea()
{

}

void SnowPea::advance(int phase)
{

    if(!phase)
        return;

    update();
    ispause=Shopcard->ispause;
   /* static int counter1=200;//词缀1
    static int counter2=200;//词缀2
    if(word1!=-1){
        counter1--;
        qDebug()<<counter1;
    }

    if(counter1==0){
        switch(word1){
        case 0:hasbomb=0;break;
        case 1:hascure=0;break;
        case 2:hasfreeze=0;break;
        case 3:haslower=0;break;
        case 4:hasshutdown=0;break;
        default:break;
        }
        hasamount--;
        word1=-1;
        counter1=100;

    }
    if(word2!=-1){
        counter2--;
    }
    if(counter2==0){
        switch(word2){
        case 0:hasbomb=0;break;
        case 1:hascure=0;break;
        case 2:hasfreeze=0;break;
        case 3:haslower=0;break;
        case 4:hasshutdown=0;break;
        default:break;
        }
        hasamount--;
        word2=-1;
        counter2=100;

    }*/
    QList <QGraphicsItem *> items = collidingItems();
    if(!items.isEmpty()){
    if(peaCounter < peaCreateTime)
        ++peaCounter;
    if(peaCounter == peaCreateTime)
    {
        foreach (QGraphicsItem *item, items)
        {
            Enemy *zombie = qgraphicsitem_cast<Enemy *>(item);
            if(zombie->posY-posY>-90&&zombie->posY-posY<180){

                if(zombie->posX>posX){
                    pea = new Pea(QPointF(posX+100, posY+70),0,1);
                    if(hasbomb)
                        pea->ATK+=6;
                    if(hasfreeze)
                        pea->slower=1;
                    scene->addItem(pea);
                }
                if(zombie->posX<posX){
                    pea = new Pea(QPointF(posX-20, posY+70),1,1);
                    if(hasbomb)
                        pea->ATK+=6;
                    if(hasfreeze)
                        pea->slower=1;
                    scene->addItem(pea);
                }
            }
            if(zombie->posX-posX>-100&&zombie->posX-posX<100){

                if(zombie->posY>posY){
                    pea = new Pea(QPointF(posX+80, posY+80),2,1);
                    if(hasbomb)
                        pea->ATK+=6;
                    if(hasfreeze)
                        pea->slower=1;
                    scene->addItem(pea);}
                if(zombie->posY<posY){
                    pea = new Pea(QPointF(posX+80 ,posY+40),3,1);
                    if(hasbomb)
                        pea->ATK+=6;
                    if(hasfreeze)
                        pea->slower=1;
                    scene->addItem(pea);}
            }
            peaCounter = 0;
        }
    }}
    if(hp <= 0){
        is_eaten=1;
        }
}
bool SnowPea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);

    return other->type() == Enemy::Type;
}
