#include"enemy.h"
Enemy::Enemy()
{
    hasdisturb=0;hasjump=0;
    hasrefresh=0;havenumber=0;
    hasfaster=0;
     speedFactor = 100;
    Factor=1;
      snowCounter = 0;
    setStatus = 1; nowStatus = 1;
    is_over=0;
    Way1=nullptr;
    Way2=nullptr;
    Way3=nullptr;
    level=-1;
    i=1;j=1;k=1;
   // label=new QLabel;
   // proxyWidget = new QGraphicsProxyWidget();

}

Enemy::~Enemy()
{

}

QRectF Enemy::boundingRect() const
{
    return QRectF(0, 0, 1800, 2000);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(option);
    Q_UNUSED(widget);
    //painter->drawImage(boundingRect(), movie->currentImage());
    // painter->drawRect(boundingRect());
    //qDebug()<<"paint"<<posY;
    if(hasjump)
        painter->drawImage(QRectF(posX+40,posY+20,30,30),QImage(":/words/Images/Others/words/jump.png"));
    if(hasrefresh)
        painter->drawImage(QRectF(posX+40,posY+20,30,30),QImage(":/words/Images/Others/words/refresh.png"));
    if(hasdisturb)
        painter->drawImage(QRectF(posX+40,posY+20,30,30),QImage(":/words/Images/Others/words/disturb.png"));
    if(hasfaster)
         painter->drawImage(QRectF(posX+40,posY+20,30,30),QImage(":/words/Images/Others/words/faster.png"));
    painter->drawImage(QRectF(posX,posY,150,150), *image);
    QBrush red_brush( QColor(0xF2,0x09,0x00));//把刷子设置为红色
    painter->setBrush(red_brush);
    float rate =nowHP/HP;//计算比例

    painter->drawRect(QRectF(posX+40,posY,80*rate,10));
}

void Enemy::advance(int phase)
{

   // update();

}

bool Enemy::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    return other->type() == Tower::Type && other->x()-posX<50 && other->x()-posX>-50
           && other->y()-posY>-50 && other->y()-posY<50;

}

int Enemy::type() const
{
    return Type;
}
void Enemy::move(int level,int road){
    float movelength=speed*Factor;
    if(hasjump) {movelength+=240;
        hasjump=0;
        havenumber--;}
    if(level==1&&road==0){
        Way way1(0,12,0,0);
        Way way2(0,11,3,0);
        Way way3(5,11,0,0);
        Way way4(5,0,4,0);
        wayList1.push_back(way1);
        wayList1.push_back(way2);
        wayList1.push_back(way3);
        wayList1.push_back(way4);


        switch(wayList1[i-1].getstate()){
        case 0://左移
            posX=posX-movelength;
            update();
            //qDebug()<<x()<<y();
            break;
        case 1://右移
            posX=posX+movelength;update();break;
        case 2://上移
            posY=posY-movelength;update();break;
        case 3://下移
            posY=posY+movelength;update();break;
        default:break;
        }
        //这里是左下左，不考虑右上移
        if(posX<wayList1[i].getposx()-40||posY>wayList1[i].getposy()-60){

            posX=wayList1[i].getposx()-40;
            posY=wayList1[i].getposy()-60;
            i++;
        }

        if(i==4){
            setX(270);
            setY(540);
        }


    }
    if(level==2&&road==0){
        Way way1(1,12,0,0);//左下左上左下左上左
        Way way2(1,10,3,0);
        Way way3(6,10,0,0);
        Way way4(6,7,2,0);
        Way way5(1,7,0,0);
        Way way6(1,4,3,0);
        Way way7(6,4,0,0);
        Way way8(6,1,2,0);
        Way way9(1,1,0,0);
        Way way10(1,0,4,0);
        wayList1.push_back(way1);
        wayList1.push_back(way2);
        wayList1.push_back(way3);
        wayList1.push_back(way4);
        wayList1.push_back(way5);
        wayList1.push_back(way6);
        wayList1.push_back(way7);
        wayList1.push_back(way8);
        wayList1.push_back(way9);
        wayList1.push_back(way10);
        switch(wayList1[i-1].getstate()){
        case 0://左移
            posX=posX-movelength;
            update();
           //qDebug()<<posX<<posY;
            break;
        case 1://右移
            posX=posX+movelength;update();break;
        case 2://上移
            posY=posY-movelength;update();break;
        case 3://下移
            posY=posY+movelength;update();break;
        default:break;
        }
        if(posX<wayList1[i].getposx()-40||(posY>wayList1[i].getposy()-60&&wayList1[i-1].getstate()==3)||(posY<wayList1[i].getposy()-60&&wayList1[i-1].getstate()==2)){

            posX=wayList1[i].getposx()-40;
            posY=wayList1[i].getposy()-60;
            i++;
        }
        if(i==10){
            setX(160);
            setY(220);
        }

    }
    if(level==3&&(road==0||road==1||road==2)){
        Way way1(0,9,3,0);//下左上左
        Way way2(6,9,0,0);
        Way way3(6,1,2,0);
        Way way4(4,1,0,0);
        Way way5(4,0,4,0);

          wayList1.push_back(way1);
        wayList1.push_back(way2);
        wayList1.push_back(way3);
        wayList1.push_back(way4);
        wayList1.push_back(way5);
        Way way6(0,3,3,1);//下左下左
        Way way7(3,3,0,1);
        Way way8(3,1,3,1);
        Way way9(4,1,0,1);
        Way way10(4,0,4,1);
         wayList2.push_back(way6);
        wayList2.push_back(way7);
        wayList2.push_back(way8);
        wayList2.push_back(way9);
        wayList2.push_back(way10);
        Way way11(4,12,0,2);//左下左上左
        Way way12(4,9,3,2);
        Way way13(6,9,0,2);
        Way way14(6,1,2,2);
        Way way15(4,1,0,2);
        Way way16(4,0,4,2);
         wayList3.push_back(way11);
        wayList3.push_back(way12);
        wayList3.push_back(way13);
        wayList3.push_back(way14);
        wayList3.push_back(way15);
        wayList3.push_back(way16);
        if(road==0){
            switch(wayList1[i-1].getstate()){
            case 0://左移
                posX=posX-movelength;
                update();
               // qDebug()<<posX<<posY;
                break;
            case 1://右移
                posX=posX+movelength;update();break;
            case 2://上移
                posY=posY-movelength;update();break;
            case 3://下移
                posY=posY+movelength;update();break;
            default:break;
            }
            if((posX<wayList1[i].getposx()-40&&wayList1[i-1].getstate()==0)||(posX>wayList1[i].getposx()-40&&wayList1[i-1].getstate()==1)||(posY>wayList1[i].getposy()-60&&wayList1[i-1].getstate()==3)||(posY<wayList1[i].getposy()-60&&wayList1[i-1].getstate()==2)){

                posX=wayList1[i].getposx()-40;
                posY=wayList1[i].getposy()-60;
                i++;
            }
            if(i==5){
                setX(160);
                setY(460);
            }
        }
        else if(road==1){
            switch(wayList2[i-1].getstate()){
            case 0://左移
                posX=posX-movelength;
                update();
                //qDebug()<<posX<<posY;
                break;
            case 1://右移
                posX=posX+movelength;update();break;
            case 2://上移
                posY=posY-movelength;update();break;
            case 3://下移
                posY=posY+movelength;update();break;
            default:break;
            }
            if((posX<wayList2[i].getposx()-40&&wayList2[i-1].getstate()==0)||(posX>wayList2[i].getposx()-40&&wayList2[i-1].getstate()==1)||(posY>wayList2[i].getposy()-60&&wayList2[i-1].getstate()==3)||(posY<wayList2[i].getposy()-60&&wayList2[i-1].getstate()==2)){

                posX=wayList2[i].getposx()-40;
                posY=wayList2[i].getposy()-60;
                i++;
            }
            if(i==5){
                setX(160);
                setY(460);
            }
        }
        else if(road==2){
            switch(wayList3[i-1].getstate()){
            case 0://左移
                posX=posX-movelength;
                update();
                //qDebug()<<posX<<posY;
                break;
            case 1://右移
                posX=posX+movelength;update();break;
            case 2://上移
                posY=posY-movelength;update();break;
            case 3://下移
                posY=posY+movelength;update();break;
            default:break;
            }
            if((posX<wayList3[i].getposx()-40&&wayList3[i-1].getstate()==0)||(posX>wayList3[i].getposx()-40&&wayList3[i-1].getstate()==1)||(posY>wayList3[i].getposy()-60&&wayList3[i-1].getstate()==3)||(posY<wayList3[i].getposy()-60&&wayList3[i-1].getstate()==2)){

                posX=wayList3[i].getposx()-40;
                posY=wayList3[i].getposy()-60;
                i++;
            }
            if(i==5){
                setX(160);
                setY(460);
            }
        }
    }
    if(level==4&&(road==0||road==1||road==2)){
        Way way1(3,12,0,0);//左
        Way way2(3,0,4,0);

        wayList1.push_back(way1);
        wayList1.push_back(way2);
        Way way3(1,0,1,1);//右下左
        Way way4(1,8,3,1);
        Way way5(3,8,0,1);
        Way way6(3,0,4,1);

          wayList2.push_back(way3);
        wayList2.push_back(way4);
        wayList2.push_back(way5);
         wayList2.push_back(way6);
        Way way7(5,0,1,2);//右下右上左
        Way way8(5,3,3,2);
        Way way9(6,3,1,2);
        Way way10(6,6,2,2);
        Way way11(3,6,0,2);
        Way way12(2,0,4,2);

         wayList3.push_back(way7);
        wayList3.push_back(way8);
        wayList3.push_back(way9);
        wayList3.push_back(way10);
        wayList3.push_back(way11);
        wayList3.push_back(way12);
        if(road==0){
            switch(wayList1[i-1].getstate()){
            case 0://左移
                posX=posX-movelength;
                update();
                // qDebug()<<posX<<posY;
                break;
            case 1://右移
                posX=posX+movelength;update();break;
            case 2://上移
                posY=posY-movelength;update();break;
            case 3://下移
                posY=posY+movelength;update();break;
            default:break;
            }
            if((posX<wayList1[i].getposx()-40&&wayList1[i-1].getstate()==0)||(posX>wayList1[i].getposx()-40&&wayList1[i-1].getstate()==1)||(posY>wayList1[i].getposy()-60&&wayList1[i-1].getstate()==3)||(posY<wayList1[i].getposy()-60&&wayList1[i-1].getstate()==2)){

                posX=wayList1[i].getposx()-40;
                posY=wayList1[i].getposy()-60;
                i++;
            }
            if(i==2){
                setX(160);
                setY(460);
            }
        }
        else if(road==1){
            switch(wayList2[i-1].getstate()){
            case 0://左移
                posX=posX-movelength;
                update();
                //qDebug()<<posX<<posY;
                break;
            case 1://右移
                posX=posX+movelength;update();break;
            case 2://上移
                posY=posY-movelength;update();break;
            case 3://下移
                posY=posY+movelength;update();break;
            default:break;
            }
            if((posX<wayList2[i].getposx()-40&&wayList2[i-1].getstate()==0)||(posX>wayList2[i].getposx()-40&&wayList2[i-1].getstate()==1)||(posY>wayList2[i].getposy()-60&&wayList2[i-1].getstate()==3)||(posY<wayList2[i].getposy()-60&&wayList2[i-1].getstate()==2)){

                posX=wayList2[i].getposx()-40;
                posY=wayList2[i].getposy()-60;
                i++;
            }
            if(i==4){
                setX(160);
                setY(460);
            }
        }
        else if(road==2){
            switch(wayList3[i-1].getstate()){
            case 0://左移
                posX=posX-movelength;
                update();
                //qDebug()<<posX<<posY;
                break;
            case 1://右移
                posX=posX+movelength;update();break;
            case 2://上移
                posY=posY-movelength;update();break;
            case 3://下移
                posY=posY+movelength;update();break;
            default:break;
            }
            if((posX<wayList3[i].getposx()-40&&wayList3[i-1].getstate()==0)||(posX>wayList3[i].getposx()-40&&wayList3[i-1].getstate()==1)||(posY>wayList3[i].getposy()-60&&wayList3[i-1].getstate()==3)||(posY<wayList3[i].getposy()-60&&wayList3[i-1].getstate()==2)){

                posX=wayList3[i].getposx()-40;
                posY=wayList3[i].getposy()-60;
                i++;
            }
            if(i==6){
                setX(160);
                setY(460);
            }
        }}
}
int Enemy::Random(int n,int min,int max)
{
    LARGE_INTEGER seed;
    QueryPerformanceFrequency(&seed);//返回硬件支持的高精度计数器的频率
    QueryPerformanceCounter(&seed);//函数返回高精确度性能计数器的值,它可以以微妙为单位计
    srand(seed.QuadPart);    //初始化一个以微秒为单位的时间种子
    int Precision = pow(10,n) - 1;

    return (int)((rand() % Precision / (float)(Precision + 1))*pow(10,n)) % max + min;
}
