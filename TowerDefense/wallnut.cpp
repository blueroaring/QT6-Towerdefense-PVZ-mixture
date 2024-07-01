#include "wallnut.h"

Wallnut::Wallnut() {}
Wallnut::Wallnut(QPointF point)
{
    hp = 4000; setStatus = 0; nowStatus = 0;
    oldHP=hp;
    movie = new QMovie(":/shopcard/Images/Plants/Wallnut/idle.gif");
    movie->start();
    posX = point.x()+10;
    posY = point.y()+10;
    setPos(posX, posY);
    state=3;
    name="Wallnut";
}

Wallnut::~Wallnut()
{
}
void Wallnut::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(0,0,110,110), movie->currentImage());
    int i=0;

    if(hasbomb){
        painter->drawImage(QRectF(15+40*i,-15,30,30),QImage(":/words/Images/Others/words/bomb.png"));
        i++;
    }
    if(hascure){
        painter->drawImage(QRectF(15+40*i,-15,30,30),QImage(":/words/Images/Others/words/cure.png"));
        i++;
    }
    if(hasfreeze){
        painter->drawImage(QRectF(15+40*i,-15,30,30),QImage(":/words/Images/Others/words/freeze.png"));
        i++;
    }

    if(haslower){
        painter->drawImage(QRectF(15+40*i,-15,30,30),QImage(":/words/Images/Others/words/lower.png"));
        i++;
    }
    if(hasshutdown){
        painter->drawImage(QRectF(15+40*i,-15,30,30),QImage(":/words/Images/Others/words/shutdown.png"));
        i++;
    }

}
void Wallnut::advance(int phase)
{
    if(hascure&&hp+10<=oldHP)
        hp+=3;

    if(!phase)
        return;
    update();
    //ispause=Shopcard->ispause;
   /* static int counter1=500;//词缀1
    static int counter2=500;//词缀2
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
    if(hp >= oldHP * 2 / 3)
        setStatus = 0;
    else if(hp >= oldHP * 1 / 3&&hp<oldHP*2/3)
        setStatus = 1;
    else if(hp > 0&&hp<oldHP*1/3)
        setStatus = 2;
    else if(hp <= 0){
        is_eaten=1;
        delete this;}
    if(setStatus != nowStatus)
        switch(setStatus)
        {
        case 0:
            delete movie;
            movie = new QMovie(":/shopcard/Images/Plants/Wallnut/idle.gif");
            movie->start();
            break;
        case 1:
            delete movie;
            movie = new QMovie(":/shopcard/Images/Plants/Wallnut/Wallnut_cracked1.gif");
            movie->start();
            break;
        case 2:
            delete movie;
            movie = new QMovie(":/shopcard/Images/Plants/Wallnut/Wallnut_cracked2.gif");
            movie->start();
            break;
        default:
            break;
        }
    nowStatus = setStatus;
}

