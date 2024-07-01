#include "caltrop.h"

Caltrop::Caltrop() {}

Caltrop::Caltrop(QPointF point){
    oldHP=5;
    hp = oldHP; setStatus = 0; nowStatus = 0;atk=1;//初始数据
    movie = new QMovie(":/shopcard/Images/Plants/Caltrop/idle.gif");//设置动画
    movie->start();
    posX = point.x()+17;
    posY = point.y()+30;
    setPos(posX, posY);
    is_caltrop=1;
    state=1;
    name="Caltrop";
}

void Caltrop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(0,0,100,100), movie->currentImage());
    int i=0;

    if(hasbomb){
        painter->drawImage(QRectF(15+40*i,0,30,30),QImage(":/words/Images/Others/words/bomb.png"));
        i++;
    }
    if(hascure){
        painter->drawImage(QRectF(15+40*i,0,30,30),QImage(":/words/Images/Others/words/cure.png"));
        i++;
    }
    if(hasfreeze){
        painter->drawImage(QRectF(15+40*i,0,30,30),QImage(":/words/Images/Others/words/freeze.png"));
        i++;
    }

    if(haslower){
        painter->drawImage(QRectF(15+40*i,0,30,30),QImage(":/words/Images/Others/words/lower.png"));
        i++;
    }
    if(hasshutdown){
        painter->drawImage(QRectF(15+40*i,0,30,30),QImage(":/words/Images/Others/words/shutdown.png"));
        i++;
    }
}
void Caltrop::advance(int phase)
{
    atk=1;
    if(hasbomb)
        atk+=1;
    static int ab=3;
    if(hasshutdown){
        atk+=1800;




    }
    //ispause=Shopcard->ispause;
    if(!phase)
        return;
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
    update();

    if(hp <= 0){
        is_eaten=1;
        scene->removeItem(this);}
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        foreach (QGraphicsItem *item, items)
        {
            Enemy *zombie = qgraphicsitem_cast<Enemy *>(item);
            if(zombie->posX-posX>-50&&zombie->posX-posX<50&&zombie->posY-posY>-50&&zombie->posY-posY<50){
                setStatus=1;
                if(!zombie->hasdisturb)
                zombie->nowHP -= atk;
                if(zombie->nowHP<=0){

                    if(hasshutdown){

                        hasshutdown=0;
                        hasamount--;
                        if(word1==4)
                            word1=-1;
                        if(word2==4)
                            word2=-1;

                    }
                }
                zombie->update();
            }



        }
    }
    if(setStatus != nowStatus)
        switch(setStatus)
        {
        case 1:
            delete movie;
            movie = new QMovie(":/shopcard/Images/Plants/Caltrop/attack.gif");
            movie->start();                     
            break;
        default:
            break;
        }
    nowStatus = setStatus;
}
bool Caltrop::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);

    return other->type() == Enemy::Type;
}
