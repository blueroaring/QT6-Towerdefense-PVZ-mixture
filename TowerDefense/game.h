#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include<QFile>
#include<QLabel>
#include<QPainter>
#include<QPushButton>
#include<QMediaPlayer>
#include<QGraphicsScene>
#include<QGraphicsView>
#include <QGraphicsSceneDragDropEvent>
#include"mapway.h"
#include"shop.h"
#include"addmap.h"
#include"shopcard.h"
#include"way.h"
#include"words.h"
namespace Ui {
class game;
}
//游戏界面
class game : public QWidget
{
    Q_OBJECT

public:
    QGraphicsScene *scene;//游戏界面
    explicit game(QWidget *parent = nullptr);//之前用的，重构后不用了
    explicit game(QWidget *parent,int level);//构造函数
    ~game();
    bool ispause;//暂停判断
    void preLoadWaves(int level);//生成地图（耦合度很高，和其他类梦幻联动）
    void pre(int waves);//存档用的
    void back_to_pre();//出错返回原来界面
   // void GeneratePath();//生成行动路径
    bool SaveGames();//实时存档
    void paintEvent(QPaintEvent *);//现在不用了
    QTimer *timer;//顾名思义，一切刷新的源头
 void addway(int level);//加入waypoint，即控制拐弯点
    int Wave;//波次
 int playerhp;//游戏血量
  int level;//关卡
  Words* words;//词缀
  mapway *map;//地图
  int mapArr[8][13];//地图数组
  QMap<int,QString> map_value_to_path;//对应的加载图片
  shopcard *Shopcard;//卡槽
private slots:
    void exit_clicked();
    void save_clicked();
    //void shovel_clicked();
    void pause_clicked();

public slots:
    void createZombie();//定时生成僵尸
    void check();//检查游戏胜利还是结束
private:
    Ui::game *ui;

    QPushButton * exitButton;//返回主界面，并link是否存档
    QPushButton *SaveButton;//存档
    QPushButton *pauseButton;
    QMediaPlayer player;
    QGraphicsView *view;

    //shovel * Shovel;//铲子
    Shop *shop;//一个商店图
    addmap *add;//没用到

   // QVector<Way> wayList;//存拐弯路径点
    Way *Way1;//用于生成路径临时存一下
    Way *Way2;
    Way *Way3;


};

#endif // GAME_H
