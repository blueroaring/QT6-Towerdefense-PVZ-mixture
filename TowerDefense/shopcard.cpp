#include "shopcard.h"
#include<QGraphicsSceneMouseEvent>
#include<QDrag>
#include<QMimeData>
#include<QApplication>
#include<QWidget>
#include<QTimer>
#include<QPainter>
#include<QMediaPlayer>
#include<QAudioOutput>
const QMap<QString, int> shopcard::map = {{"Repeater", 0}, {"Peashooter", 1}, {"CherryBomb", 2}, {"WallNut", 3},//未来会改
                                          {"SnowPea", 4}, {"cutt", 5},{"Chomper",6}};
const QVector<QString> shopcard::name = {"Repeater", "Peashooter", "CherryBomb", "WallNut",
                                     "SnowPea", "cutt","Chomper"};
const QVector<int> shopcard::cost = {200, 100, 150, 50, 175, 100,150};

shopcard::shopcard(){
   // qDebug()<<"shopcardused";
    sunNeed = -1; readyPlanted = 0;
    setCursor(Qt::PointingHandCursor);
    setZValue(2);
    NO=-1;
    ispause=0;
    sunTotal = 5000;




}
shopcard::~shopcard(){}
QRectF shopcard::boundingRect() const
{
    return QRectF(200, 50, 850, 130);
}

void shopcard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{


    Q_UNUSED(option);
    Q_UNUSED(widget);
    //qDebug()<<"paint";
    for(int i=0;i<7;i++){
    QImage image1(":/new/Image/Images/Others/controller/Card.png");
    painter->drawImage(QRectF(360+i*100,50,100,120), image1);
    QImage image(":/cards/Images/Plants/shopcard/" + name[i] + ".png");
        painter->drawImage(QRectF(370+i*100,65,70,70), image);
    painter->setFont(QFont("Arial", 15));
        painter->drawText(390+i*100, 160, QString::number(cost[i]));
    }
    QString a=QString::number(sunTotal);
   // qDebug()<<a;
    painter->setPen(Qt::darkGray);
    painter->drawText(QRectF(260, 150,50,50), a);

}


void shopcard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if(event->button()==Qt::LeftButton&&!ispause)
    {

       // qDebug()<<(int)event->scenePos().x();
         hex= (((int)event->scenePos().x() - 360) / 100);
        if(hex>=0){
        NO=hex;
        sunNeed=cost[hex];
        if(sunTotal >= sunNeed){
            QCursor cursor(QPixmap(":/cards/Images/Plants/shopcard/" + name[hex] + ".png"));
            this->setCursor(cursor);
            readyPlanted=1;
            QMediaPlayer *win=new QMediaPlayer;
            QAudioOutput *Win=new QAudioOutput;
            win->setAudioOutput(Win);
            win->setSource(QUrl("../Music/seedlift.mp3"));
            Win->setVolume(50);
            win->setLoops(QMediaPlayer::Once);
            win->play();
           // qDebug() << "CardClicked!" ;
        }}
    }
}

void shopcard::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);
}
void shopcard::advance(int phase){
    static int counter=0,more=150;
    Q_UNUSED(phase);
    counter++;
    if(counter==more&&sunTotal<=6000){
        counter=0;
        sunTotal+=50;
        update();
    }

}
