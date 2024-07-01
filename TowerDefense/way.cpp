#include "way.h"
#include<QPoint>
#include<QDebug>
Way::Way(int y,int x,int State,int choose) :now_nextWayPoint(nullptr),state(State),way_choose(choose){
    posx=x;
    posy=y;
}
void Way::setNextWayPoint(Way nextPoint){
    now_nextWayPoint=&nextPoint;

}
int Way::getposx() const{
    return 200+posx*80;
}
int Way::getposy() const{
    return 200+posy*80;
}
int Way::getstate() const{
    return state;
}
int Way::getchoose() const{
    return way_choose;
}
