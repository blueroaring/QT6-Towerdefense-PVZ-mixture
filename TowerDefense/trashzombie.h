#ifndef TRASHZOMBIE_H
#define TRASHZOMBIE_H
#include"enemy.h"
//铁桶僵尸
class trashzombie: public Enemy
{
public:
    trashzombie();
    trashzombie(QPointF point,int level,int Road);
    int counter;
    int road;//走哪一条道

public slots:
    void advance(int phase);
};

#endif // TRASHZOMBIE_H
