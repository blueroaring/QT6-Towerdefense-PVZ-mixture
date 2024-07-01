#ifndef WAY_H
#define WAY_H
#include<QPoint>
#include<QPainter>
//路径
class Way
{
private:
    int  posx;
    int posy;
    int state;//0,向左走，1，向右走，2，向上走，3，向下走,4,到家了
    int way_choose;//不同的值对应了不同的路径敌人
public:
    Way(int x,int y,int state,int choose);
    void setNextWayPoint(Way next);//没用到（其实因为指针出bug问题太多）
    int getposx()const ;//获得x
    int getposy()const;//获得y
    int getstate()const;//获得状态（哪个僵尸）
    int getchoose() const;//获得道路
    Way * now_nextWayPoint;//没用上

};

#endif // WAY_H
