#include "words.h"
const QVector<QString> Words::name = {"bomb", "cure", "freeze", "lower",
                                         "shutdown"};

Words::Words() {
    setCursor(Qt::PointingHandCursor);
    setZValue(2);
    for(int i=0;i<5;i++)
        wordamount[i]=10;
    ispause=0;
    prepared=-1;
}
QRectF Words::boundingRect() const
{
    return QRectF(0, 180, 200, 880);
}
void Words::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{


    Q_UNUSED(option);
    Q_UNUSED(widget);
    //qDebug()<<"paint";
    for(int i=0;i<5;i++){

        QImage image(":/words/Images/Others/words/" + name[i] + ".png");
        painter->drawImage(QRectF(0,180+130*i,150,130), image);
        painter->setFont(QFont("Arial", 40));
        painter->drawText(150, 320+130*i, QString::number(wordamount[i]));
    }


}
void Words::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if(event->button()==Qt::LeftButton&&!ispause)
    {
        int i=(((int)event->scenePos().y()-180) / 130);
        if(i>=0&&i<=4&&wordamount[i]>0){
            QCursor cursor(QPixmap(":/words/Images/Others/words/" + name[i] + ".png"));
            this->setCursor(cursor);
            ready=1;
            prepared=i;
        }

    }
}

void Words::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);
}
void Words::advance(int phase){

}

