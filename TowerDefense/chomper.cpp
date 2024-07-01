#include "chomper.h"
#include<QRandomGenerator>
#include<QMediaPlayer>
#include<QAudioOutput>
Chomper::Chomper() {

}
Chomper::Chomper(QPointF point){
    oldHP=2000;
    hp = oldHP; setStatus = 0; nowStatus = 0;atk=3;oldHP=2000;
    movie = new QMovie(":/shopcard/Images/Plants/Chomper/idle.gif");
    movie->start();
    posX = point.x()+15;
    posY = point.y();
    setPos(posX, posY);
    update();
    state=1;
    name="Chomper";


}
void Chomper::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(0,0,130,130), movie->currentImage());
    int i=0;
   // qDebug()<<"a";
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
    QBrush red_brush( QColor(0xF2,0x09,0x00));//把刷子设置为红色
    painter->setBrush(red_brush);
    float rate =hp/oldHP;//计算比例

    painter->drawRect(QRectF(20,20,80*rate,10));
}
void Chomper::advance(int phase)
{
    atk=3;
    if(hasbomb)
        atk+=1;
    if(hascure&&hp+10<=oldHP)
        hp+=3;
    static int ab=3;
    if(hasshutdown){
        atk+=1800;



    }

    //ispause=Shopcard->ispause;
    /*static int counter1=200;//词缀1
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
    int i=0;//单攻
    if(!phase)
        return;
    update();
    setStatus=0;
    if(hp <= 0){
        is_eaten=1;

        scene->removeItem(this);
        }
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        foreach (QGraphicsItem *item, items)
        {
            Enemy *zombie = qgraphicsitem_cast<Enemy *>(item);
            if(!haslower){
            if(zombie->posX-posX>-130&&zombie->posX-posX<130&&zombie->posY-posY>-120&&zombie->posY-posY<140&&i==0){
            setStatus=1;
                if(!zombie->hasdisturb)
                zombie->nowHP -= atk;

            if(zombie->nowHP<=0){



                if(hasshutdown){
                    hasshutdown=0;

                    hasamount--;
                    qDebug()<<hasamount;
                    if(word1==4)
                        word1=-1;
                    if(word2==4)
                        word2=-1;

                }
                }

            i++;
                static int counter1=0;
            if(counter1%40==0){
                QMediaPlayer *win=new QMediaPlayer;
                QAudioOutput *Win=new QAudioOutput;
                win->setAudioOutput(Win);
                win->setSource(QUrl("../Music/bigchomp.mp3"));
                Win->setVolume(50);
                win->setLoops(QMediaPlayer::Once);
                win->play();}
            counter1++;
            zombie->update();
            }}
            else{
                if(zombie->posX-posX>-130&&zombie->posX-posX<130&&zombie->posY-posY>-120&&zombie->posY-posY<140){
                    setStatus=1;
                    if(!zombie->hasdisturb)
                    zombie->nowHP -= atk;
                    if(zombie->nowHP<=0){
                        ab--;
                        if(ab==0){
                            hasshutdown=0;
                            hasamount--;
                            if(word1==4)
                                word1=-1;
                            if(word2==4)
                                word2=-1;
                            ab=3;
                        }
                    }
                    static int counter=0;

                    if(counter%40==0){
                    QMediaPlayer *win=new QMediaPlayer;
                    QAudioOutput *Win=new QAudioOutput;
                    win->setAudioOutput(Win);
                    win->setSource(QUrl("../Music/bigchomp.mp3"));
                    Win->setVolume(50);
                    win->setLoops(QMediaPlayer::Once);
                    win->play();}
                    counter++;
                    zombie->update();}
            }



        }
    }

    if(setStatus != nowStatus)
        switch(setStatus)
        {
        case 0:
            delete movie;
            movie = new QMovie(":/shopcard/Images/Plants/Chomper/idle.gif");
            movie->start();
            break;
        case 1:
            delete movie;
            movie = new QMovie(":/shopcard/Images/Plants/Chomper/bite.gif");
            movie->start();
            break;
        default:
            break;
        }
    nowStatus = setStatus;



}

bool Chomper::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);

 return other->type() == Enemy::Type;
}

