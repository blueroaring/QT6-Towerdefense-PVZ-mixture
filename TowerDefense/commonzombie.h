#ifndef COMMONZOMBIE_H
#define COMMONZOMBIE_H
#include"enemy.h"
#include<QTimer>
//普通僵尸
class commonZombie: public Enemy
{
public:
    commonZombie(QPointF point,int level,int Road);//point:生成位置  level:关卡  road:路径 level和road是createzombie用的

    int counter;//刷新计数器
    int road;//走哪一条道

public slots:
    void advance(int phase);//更新实时状态
};

#endif // COMMONZOMBIE_H
