#ifndef TOWER_H
#define TOWER_H
#include<QGraphicsItem>
#include<QMovie>
#include<QPainter>
#include<QGraphicsScene>
#include"shopcard.h"
#include"words.h"
class Tower: public QGraphicsItem
{
public:
    enum { Type = UserType + 1};//用于判断碰撞箱
    Tower();
    int hp;//现在实时血量
    QString name;//塔名称（存档时用）
    static int c1,c2;//干什么的忘了，反正是用来更新状态的
    int oldHP;//原先血量
    int level;//现在的塔的等级
    int state;//近战还是远程塔
    ~Tower() override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
   // bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int type() const override;//返回类型
    void advance(int phase) override;
    void setMovie(QString path);//设置动画逐帧播放
    QGraphicsScene *scene;
    bool is_eaten;//被吃掉、删除（爆炸）等非自然产出情况
    bool is_caltrop;//判定是不是地刺（地刺不会阻挡敌人）
    int posX,posY;
    bool ispause;
    bool hasbomb;//拥有狂暴（攻击，攻速增加）
    bool hascure;//拥有治疗（每个timer固定回复）
    bool hasfreeze;//拥有冰冻（一定时间内定住敌人）
    bool haslower;//群伤（近战塔）
    bool hasshutdown;//斩杀（有次数限制，直接杀死敌人）
    int hasamount;//拥有词缀数量
    int word1;//词缀1
    int word2;//词缀2
    shopcard*Shopcard;
    Words *words;
    int Random(int n,int min,int max);//生成毫秒级随机数
protected:
    QMovie *movie;//塔动画
    float atk;//攻击力

    int counter;//计时用
    int time;
};

#endif // TOWER_H
