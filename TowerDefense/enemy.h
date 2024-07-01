#ifndef ENEMY_H
#define ENEMY_H
#include"way.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include "tower.h"
#include"way.h"
#include<QLabel>
#include<QGraphicsProxyWidget>
#include<QGraphicsScene>
#include<QImage>
#include<QTimer>
#include"words.h"
#include<QRandomGenerator>
#include <sys/timeb.h>
#include <time.h>
#include<windows.h>
class Enemy : public QGraphicsItem
{
public:
    enum { Type = UserType + 2};//用于item碰撞箱判定
    float HP, nowHP;//最大血量，当前血量
     int ATK,nowATK;//正常攻击，现在攻击
    int setStatus;//状态
    float speedFactor;//攻击速率
    float Factor;//移动速率
    Enemy();
    ~Enemy();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int type() const override;
    bool is_over;//要删除
    Way* Way1;//第一可能路径
    Way * Way2;
    Way * Way3;
    int level;//关卡
    void move(int level,int road);//移动逻辑
   // QGraphicsProxyWidget *proxyWidget ;
    QGraphicsScene *scene;//link这个游戏界面
    QVector<Way> wayList1;//将waypoint存入
    QVector<Way> wayList2;
    QVector<Way> wayList3;
    int i,j,k;//地图移动计数器
   float posX, posY;
    int havenumber;//拥有词缀数目
   bool hasjump;//闪现词缀   0
   bool hasrefresh;//免控   1
   bool hasdisturb;//沉默防御塔  2
   bool hasfaster;//疾跑    3
   Words *words;
   public slots:
    void advance(int phase)override;
       int Random(int n,int min,int max);//生成随机数函数，从csdn学的毫秒级，秒级的随机数生成的结果是一样的不行
protected:
    int nowStatus, snowCounter;//雪球减速计数
    //QLabel * label;
    Tower *plant;//植物（用于被吃判定）
    float speed;//算出来后的真实速度
    //QString name;
    //QMovie *movie;
    QImage* image;//僵尸图片


};

#endif // ENEMY_H
