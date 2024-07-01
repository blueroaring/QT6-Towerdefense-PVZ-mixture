#include "mapway.h"
#include"reused.h"
#include <QGraphicsSceneDragDropEvent>
#include"shovel.h"
#include<QGraphicsScene>
#include<QCursor>
#include "wallnut.h"
#include "chomper.h"
#include "snowpea.h"
#include "peashooter.h"
#include"caltrop.h"
#include "cherrybomb.h"
#include"repeater.h"
#include<QTimer>
#include<QMediaPlayer>
#include<QAudioOutput>
mapway::mapway() {
    dragOver = false;
    setAcceptDrops(true);
    for(int i=0;i<8;i++)
        for(int j=0;j<13;j++){
            plantmap[i][j]=nullptr;
        }
    Shovel=new shovel;
    setAcceptHoverEvents(true);
    ispause=0;
}
mapway::~mapway(){
    for(int i = 0; i < 8; ++i)
        for(int j = 0; j < 13; ++j)
            delete plantmap[i][j];
}
void mapway::paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    for(int i=0;i<8;i++)
        for(int j=0;j<13;j++){
            painter->drawPixmap(QRect(j * blocklen+200, i * blocklen+200,blocklen,blocklen), QPixmap(map_value_to_path[mapArr[i][j]]));
        }
}
QRectF mapway::boundingRect() const
{
    return QRectF(200, 200, 1240, 1040);
}
void mapway::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(PreparedPlant->readyPlanted && event->button()==Qt::LeftButton&&!ispause)
    {
        Shovel->shovel_clicked = false;
        int j = ((int)event->scenePos().x() - 200) / 80;
        int i = ((int)event->scenePos().y() - 200) / 80;
       // qDebug()<<j<<i;
        if(!plantmap[i][j])
        {
            bool get=false;
            QPointF plantPos(200+80*j-30, 200+80*i-60);
            qDebug()<<plantPos;
            if (mapArr[i][j]==3){//是远程格子
            switch(PreparedPlant->NO)
            {
            case 0: plantmap[i][j] = new repeater(plantPos);get=true; break;
            case 1: plantmap[i][j] = new PeaShooter(plantPos);get=true; break;
            case 2: get=false; break;
            case 3: get=false; break;
            case 4: plantmap[i][j] = new SnowPea(plantPos);get=true; break;
            case 5: get=false; break;
            case 6: get=false; break;
            default:get=false; break;

            }
            if(get){
                QMediaPlayer *win=new QMediaPlayer;
                QAudioOutput *Win=new QAudioOutput;
                win->setAudioOutput(Win);
                win->setSource(QUrl("../Music/plant.mp3"));
                Win->setVolume(50);
                win->setLoops(QMediaPlayer::Once);
                win->play();
            plantmap[i][j]->setZValue(j);//z值越大就在越顶层
            plantmap[i][j]->scene=this->scene;
            plantmap[i][j]->Shopcard=this->Shopcard;
            scene->addItem(plantmap[i][j]);
           // qDebug()<<j<<i;
            this->unsetCursor();
            PreparedPlant->sunTotal -= PreparedPlant->sunNeed;
            PreparedPlant->readyPlanted=0;
         //  PreparedPlant->update();

            //qDebug()<<PreparedPlant->sunTotal;
            }
            }
            else if (mapArr[i][j]==1){//是近战格子
                switch(PreparedPlant->NO)
                {
                case 0: get=false; break;
                case 1: get=false; break;
                case 2: plantmap[i][j]=new CherryBomb(plantPos);get=true; break;
                case 3: plantmap[i][j] = new Wallnut(plantPos);get=true; break;
                case 4: get=false; break;
                case 5: plantmap[i][j] = new Caltrop(plantPos);get=true; break;
                case 6: plantmap[i][j] = new Chomper(plantPos);get=true; break;
                default: get=false;break;
                }
                if(get){
                    QMediaPlayer *win=new QMediaPlayer;
                    QAudioOutput *Win=new QAudioOutput;
                    win->setAudioOutput(Win);
                    win->setSource(QUrl("../Music/plant.mp3"));
                    Win->setVolume(50);
                    win->setLoops(QMediaPlayer::Once);
                    win->play();
                plantmap[i][j]->setZValue(j);
                    plantmap[i][j]->words=this->words;
                plantmap[i][j]->scene=this->scene;
                scene->addItem(plantmap[i][j]);
                this->unsetCursor();
                PreparedPlant->readyPlanted=0;
                PreparedPlant->sunTotal -= PreparedPlant->sunNeed;
                PreparedPlant->update();
                if(PreparedPlant->NO==2){
                    plantmap[i][j]=nullptr;
                }
                }

            }
        }
    }

    if(Shovel->shovel_clicked==true && event->button()==Qt::LeftButton&&!ispause)
    {

        int i = ((int)event->scenePos().x() - 200) / 80;
        int j = ((int)event->scenePos().y() - 200) / 80;
        //qDebug()<<i<<j<<plantmap[j][i];
        if(plantmap[j][i]){
            //qDebug()<<"used delete";
        delete plantmap[j][i];
        plantmap[j][i] = nullptr;}
        //qDebug()<<"mapwayused";
        Shovel->shovel_clicked = false;
        QCursor cursor1;
        this->setCursor(cursor1);
        QMediaPlayer *win=new QMediaPlayer;
        QAudioOutput *Win=new QAudioOutput;
        win->setAudioOutput(Win);
        win->setSource(QUrl("../Music/plant.mp3"));
        Win->setVolume(50);
        win->setLoops(QMediaPlayer::Once);
        win->play();
    }
    if(event->button()==Qt::RightButton)
    {
        Shovel->shovel_clicked=false;
        QCursor cursor1;
        this->setCursor(cursor1);

    }
    if(words->ready&&event->button()==Qt::LeftButton&&!ispause){
         int i = ((int)event->scenePos().x() - 200) / 80;
        int j = ((int)event->scenePos().y() - 200) / 80;
         if(plantmap[j][i]&&plantmap[j][i]->hasamount<2){
            if(words->prepared==0&&!plantmap[j][i]->hasbomb){
                 plantmap[j][i]->hasbomb=1;
                if(plantmap[j][i]->hasamount==0)
                     plantmap[j][i]->word1=0;
                else
                    plantmap[j][i]->word2=0;
                plantmap[j][i]->hasamount++;
                 words->wordamount[words->prepared]--;
             }
            else if(words->prepared==1&&!plantmap[j][i]->hascure&&(plantmap[j][i]->state==1||plantmap[j][i]->state==3)){

                    plantmap[j][i]->hascure=1;
                    if(plantmap[j][i]->hasamount==0)
                        plantmap[j][i]->word1=1;
                    else
                        plantmap[j][i]->word2=1;
                     plantmap[j][i]->hasamount++;
                     words->wordamount[words->prepared]--;

            }
             else if(words->prepared==2&&!plantmap[j][i]->hasfreeze&&plantmap[j][i]->state==2){
                 plantmap[j][i]->hasfreeze=1;
                 if(plantmap[j][i]->hasamount==0)
                     plantmap[j][i]->word1=2;
                 else
                     plantmap[j][i]->word2=2;
                  plantmap[j][i]->hasamount++;
                 words->wordamount[words->prepared]--;
             }
            else if(words->prepared==3&&!plantmap[j][i]->haslower&&plantmap[j][i]->state==1){
                plantmap[j][i]->haslower=1;
                if(plantmap[j][i]->hasamount==0)
                    plantmap[j][i]->word1=3;
                else
                    plantmap[j][i]->word2=3;
                 plantmap[j][i]->hasamount++;
                words->wordamount[words->prepared]--;
            }
             else if(words->prepared==4&&!plantmap[j][i]->hasshutdown&&plantmap[j][i]->state==1){
                 plantmap[j][i]->hasshutdown=1;
                 if(plantmap[j][i]->hasamount==0)
                     plantmap[j][i]->word1=4;
                 else
                     plantmap[j][i]->word2=4;
                  plantmap[j][i]->hasamount++;
                 words->wordamount[words->prepared]--;
             }

            plantmap[j][i]->update();
        }


         words->prepared=-1;
        words->ready=0;
         words->update();

    }
    if(event->button()==Qt::RightButton&&!ispause)
    {
        int i = ((int)event->scenePos().x() - 200) / 80;
        int j = ((int)event->scenePos().y() - 200) / 80;
        if(plantmap[j][i]){
            if(plantmap[j][i]->word1!=-1){
                switch(plantmap[j][i]->word1){
                case 0:plantmap[j][i]->hasbomb=0;break;
            case 1:plantmap[j][i]->hascure=0;break;
            case 2:plantmap[j][i]->hasfreeze=0;break;
            case 3:plantmap[j][i]->haslower=0;break;
            case 4:plantmap[j][i]->hasshutdown=0;break;
            default:break;
            }
            plantmap[j][i]->hasamount--;
            plantmap[j][i]->word1=-1;
        }
        else if(plantmap[j][i]->word2!=-1){
            switch(plantmap[j][i]->word2){
            case 0:plantmap[j][i]->hasbomb=0;break;
            case 1:plantmap[j][i]->hascure=0;break;
            case 2:plantmap[j][i]->hasfreeze=0;break;
            case 3:plantmap[j][i]->haslower=0;break;
            case 4:plantmap[j][i]->hasshutdown=0;break;
            default:break;
            }
            plantmap[j][i]->hasamount--;
            plantmap[j][i]->word2=-1;
        }
        }
    }
}
void mapway::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    if(Shovel->shovel_clicked==true&&event->isAccepted()){
       // qDebug()<<"hoverused";

        QCursor cursor(QPixmap(":/new/Image/Images/Others/controller/menulist/showel.png"), 10, 10);
        // 设置光标
        this->setCursor(cursor);

    }
    if(PreparedPlant->readyPlanted&&event->isAccepted()){

        QCursor cursor(QPixmap(":/cards/Images/Plants/shopcard/" + PreparedPlant->name[PreparedPlant->hex] + ".png"));
        this->setCursor(cursor);
    }

}
void mapway::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
}
void mapway::advance(int phase){
    Q_UNUSED(phase);
    for(int i=0;i<8;i++)
        for(int j=0;j<13;j++){
            if(plantmap[i][j]&&plantmap[i][j]->is_eaten){
                plantmap[i][j]=nullptr;
            }
        }
}
