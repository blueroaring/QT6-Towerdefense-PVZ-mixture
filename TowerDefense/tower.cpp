#include "tower.h"
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include<QRandomGenerator>
#include<Windows.h>
#include<QMediaPlayer>
#include<QAudioOutput>
Tower::Tower():movie(nullptr),atk(0),counter(0),state(0),time(0),is_eaten(0),is_caltrop(0)
{
    word1=-1;
    word2=-1;
    hasbomb=0;
    hascure=0;
    hasamount=0;
    hasfreeze=0;
    haslower=0;
    hasshutdown=0;
    ispause=0;
    words=nullptr;



}

Tower::~Tower()
{
    delete movie;
}

QRectF Tower::boundingRect() const
{
    return QRectF(0, 0, 150, 150);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(), movie->currentImage());
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

/*bool Tower::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 30;
}*/

int Tower::type() const
{
    return Type;
}

void Tower::setMovie(QString path)
{
    if (movie)
        delete movie;
    movie = new QMovie(path);
    movie->start();
}
void Tower::advance(int phase)
{
    Q_UNUSED(phase);


   /* static int counter1=100;//词缀1
    static int counter2=100;//词缀2
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
   /* qDebug()<<"used";
    if(!phase)
        return;
    if(hasamount==1&&c1==0)
    {counter1=0;
        c1++;
    }
    if(hasamount==2&&c2==0)
    {counter2=0;
        c2++;
    }
    counter1++;
    counter2++;
    if(counter1==100){
        switch(word1){
        case 0:hasbomb=0;word1=-1;hasamount--;break;
        case 1:hascure=0;word1=-1;hasamount--;break;
        case 2:hasfreeze=0;word1=-1;hasamount--;break;
        case 3:haslower=0;word1=-1;hasamount--;break;
        case 4:hasshutdown=0;word1=-1;hasamount--;break;
        default:break;

        }
        c1--;
    }
    if(counter2==100){
        switch(word2){
    case 0:hasbomb=0;word2=-1;hasamount--;break;
    case 1:hascure=0;word2=-1;hasamount--;break;
    case 2:hasfreeze=0;word2=-1;hasamount--;break;
    case 3:haslower=0;word2=-1;hasamount--;break;
    case 4:hasshutdown=0;word2=-1;hasamount--;break;
    default:break;
    }
    c2--;
    }
    update();*/

}
int Tower::Random(int n,int min,int max)
{
    LARGE_INTEGER seed;
    QueryPerformanceFrequency(&seed);//返回硬件支持的高精度计数器的频率
    QueryPerformanceCounter(&seed);//函数返回高精确度性能计数器的值,它可以以微妙为单位计
    srand(seed.QuadPart);    //初始化一个以微秒为单位的时间种子
    int Precision = pow(10,n) - 1;

    return (int)((rand() % Precision / (float)(Precision + 1))*pow(10,n)) % max + min;
}

