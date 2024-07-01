#ifndef FOOTBALLZOMBIE_H
#define FOOTBALLZOMBIE_H
#include"enemy.h"
//橄榄球僵尸
class footballzombie: public Enemy
{
public:
    footballzombie();
    footballzombie(QPointF point,int level,int Road);
    int counter;
    int road;//走哪一条道

public slots:
    void advance(int phase);
};

#endif // FOOTBALLZOMBIE_H
