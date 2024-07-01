#include "commonzombie.h"
#include<QThread>
#include<QMediaPlayer>
#include<QAudioOutput>
commonZombie::commonZombie(QPointF point,int Level,int Road)
{
    road=Road;
    level=Level;
    HP=400;nowHP=HP;
    ATK = 10; speed = 2;
   // name = "Zombie";
    //movie = new QMovie(":/Zombies/Images/Zombies/Zombie/normal/walk.gif");
    //label->setMovie(movie);
    posX = point.x();
    posY = point.y();
   // proxyWidget->setWidget(label);
   // label->setScaledContents(true);
   // label->setFixedSize(QSize(150,150));
   // proxyWidget->setPos(posX, posY);
   // movie->start();
    image=new QImage(":/Zombies/Images/Zombies/Zombie/need/walk.png");
    counter=0;
    setStatus=1;

}

void commonZombie::advance(int phase)
{


    if(!phase)
        return;
    update();


    QList <QGraphicsItem *> items = collidingItems();


        if(nowHP > 0){
            setStatus = 1;
           // qDebug()<<items.isEmpty();
            if(!items.isEmpty()){   // 如果碰到植物

                plant = qgraphicsitem_cast<Tower *> (items[rand() % items.size()]);

                if(!plant->is_caltrop){
                setStatus = 2;
                    if(!hasjump)
                    stackBefore(plant);

                }
            }
        }
        else
        {setStatus = 0;
            }



    switch(setStatus)
    {

    case 0:
        speedFactor = 100;
        if(setStatus != nowStatus)
        {
            delete image;
            image = new QImage(":/Zombies/Images/Zombies/Zombie/need/death.png");

            update();

        }
        counter+=1;
        if(counter==5){
            //qDebug()<<-2;

            int Rand=Random(1,0,60);
            if(Rand>=0&&Rand<=4&&words)
            {
                words->wordamount[Rand]++;
            }
            scene->removeItem(this);
            delete this;}
        break;
    case 1:
        if(setStatus != nowStatus)
        {
            delete image;
            image = new QImage(":/Zombies/Images/Zombies/Zombie/need/walk.png");
            update();

        }

        move(level,road);
        break;
    case 2:{
        if(setStatus != nowStatus)
        {
            QMediaPlayer *win=new QMediaPlayer;
            QAudioOutput *Win=new QAudioOutput;
            win->setAudioOutput(Win);
            win->setSource(QUrl("../Music/chompsoft.mp3"));
            Win->setVolume(50);
            win->setLoops(QMediaPlayer::Once);
            win->play();
            delete image;
            image = new QImage(":/Zombies/Images/Zombies/Zombie/need/eat(2).png");
            update();

        }
       // qDebug()<<plant->hp;
        plant->hp -= ATK  * speedFactor / 100;
        if(plant->hp<=500){
        int Rand1=Random(1,0,4);
        if(Rand1>=0&&Rand1<=3)
        {

            switch(Rand1){
            case 0:{if(!hasjump&&havenumber==0){hasjump=1;havenumber++;}break;}
            case 1:{if(!hasrefresh&&havenumber==0){hasrefresh=1;havenumber++;}break;}
            case 2:{if(!hasdisturb&&havenumber==0){hasdisturb=1;havenumber++;}break;}
            case 3:{if(!hasfaster&&havenumber==0){hasfaster=1;havenumber++;}break;}
            default:break;
            }
        }}
        if(plant->hp<=0){

        plant->is_eaten=1;
        plant->update();}
        break;}
    default:
        break;
    }
    nowStatus = setStatus;
    if(!items.empty())
        items.clear();
    static int counter1;
    if(Factor!=1){
        counter1++;
        if(counter1==50){
            counter1=0;
            Factor=1;
        }
    }
    if(hasfaster){
        speed+=0.015;
    }

}
