#include "game.h"
#include "ui_game.h"
#include"maps.h"
#include"shop.h"
#include"words.h"
#include"enemy.h"
#include"commonzombie.h"
#include"way.h"
#include <QJsonObject> // { }
#include <QJsonArray> // [ ]
#include <QJsonDocument> // 解析Json
#include <QJsonValue> // int float double bool null { } [ ]
#include <QJsonParseError>
#include<QFile>
#include<QString>
#include<QMessageBox>
#include<QPixmap>
#include<QPainter>
#include<QGraphicsPixmapItem>
#include<QImage>
#include<QPaintEvent>
#include<QPushButton>
#include"mainwindow.h"
#include<QAudioOutput>
#include<QMediaPlayer>
#include<QDebug>
#include<QTimer>
#include"trashzombie.h"
#include"footballzombie.h"
 int kind1 = 0;
 int kind2 = 0;
 int kind3 = 0;
 int wave=1;
game::game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::game)
{

    /*scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    scene->setSceneRect(0, 0, 1140, 740);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    view->setAcceptDrops(true);
    this->setAcceptDrops(true);
    scene->addItem(map);
    shop = new Shop;
    scene->addItem(shop);
    shopcard *Shopcard=new shopcard;
    map->PreparedPlant=Shopcard;
    Shopcard->scene=scene;
    scene->addItem(Shopcard);
    map->shop=shop;
    qDebug()<<"do";
    //Shovel=new shovel;
    //scene->addItem(Shovel);
    scene->addItem(map->Shovel);
    view->show();
    view->resize(1240, 200);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QAudioOutput *audioOutput=new QAudioOutput(this);
    player.setAudioOutput(audioOutput);
    player.setSource(QUrl("../Music/Laura Shigihara - Zombies on Your Lawn [mqms2].mp3"));
    audioOutput->setVolume(50);
    player.play();
    this->setWindowIcon(QIcon(":/new/Image/Images/Others/Scenes/icon.png"));
    this->setMinimumSize(1340,1040);
    this->setMaximumSize(1340,1040);

    this->exitButton = new QPushButton("退出",this);
    this->exitButton->setGeometry(1140,0,100,50);
    exitButton->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    connect(exitButton,SIGNAL(clicked(bool)),this,SLOT(exit_clicked()));
    this->SaveButton = new QPushButton("存档",this);
    this->SaveButton->setGeometry(1140,50,100,50);
    SaveButton->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    connect(SaveButton,SIGNAL(clicked(bool)),this,SLOT(save_clicked()));
    this->pauseButton = new QPushButton("暂停",this);
    this->pauseButton->setGeometry(1140,100,100,50);
    pauseButton->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    connect(pauseButton,SIGNAL(clicked(bool)),this,SLOT(pause_clicked()));
    ui->setupUi(this);*/

}
game::game(QWidget *parent,int level)
    : QWidget(parent)
    , ui(new Ui::game){
    wave=1;
    kind1=0;
    kind2=0;
    kind3=0;
    Wave=wave;
    playerhp=5;
    ispause=false;
    this->level=level;
    preLoadWaves(level);
    addway(level);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    scene->setSceneRect(0, 0, 1240,840);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    view->setMouseTracking(true);
    view->setAcceptDrops(true);
    this->setAcceptDrops(true);
    scene->addItem(map);
    map->scene=this->scene;
    scene->addItem(map->Shovel);
    shop = new Shop;
    scene->addItem(shop);
    Shopcard=new shopcard();
    map->PreparedPlant=Shopcard;
    scene->addItem(Shopcard);
    map->Shopcard=Shopcard;
    view->show();
    view->resize(1240,840);//疑似是这个坐标系
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QAudioOutput *audioOutput=new QAudioOutput(this);
    player.setAudioOutput(audioOutput);
    player.setSource(QUrl("../Music/Laura Shigihara - Graze the Roof.mp3"));
    if(level==4)
        player.setSource(QUrl("../Music/Laura Shigihara - Brainiac Maniac [mqms2].mp3"));
    audioOutput->setVolume(50);
    player.setLoops(QMediaPlayer::Infinite);
    player.play();
    words=new Words;

    words->scene=scene;
    scene->addItem(words);
    map->words=words;
    //qDebug()<<"change";
    this->setMinimumSize(1240,840);//疑似没用
    this->setMaximumSize(1240,840);
    this->setWindowIcon(QIcon(":/new/Image/Images/Others/Scenes/icon.png"));
    this->exitButton = new QPushButton("退出",this);
    this->exitButton->setGeometry(1140,0,100,50);
    exitButton->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    connect(exitButton,SIGNAL(clicked(bool)),this,SLOT(exit_clicked()));
    if(level!=5){
    this->SaveButton = new QPushButton("存档",this);
    this->SaveButton->setGeometry(1140,50,100,50);
    SaveButton->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    connect(SaveButton,SIGNAL(clicked(bool)),this,SLOT(save_clicked()));}
    this->pauseButton = new QPushButton("暂停",this);
    this->pauseButton->setGeometry(1140,100,100,50);
    pauseButton->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    connect(pauseButton,SIGNAL(clicked(bool)),this,SLOT(pause_clicked()));
    ui->setupUi(this);
    timer = new QTimer;
    timer->start(33);
    QTimer *timer2=new QTimer;
    timer2->start(33);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer2,SIGNAL(timeout()), this, SLOT(createZombie()));
    connect(timer2, SIGNAL(timeout()), this,SLOT(check()));

}

game::~game()
{
    delete ui;
}
void game::preLoadWaves(int level){

    if(level==1){//4:家，0:水上不可种格，未来可能会补荷叶 ， 3：可种格  2：出怪口  1：路径
        int mapArr_1[8][13]={
            0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 1, 2,
            3, 3, 3, 3, 0, 3, 0, 3, 3, 3, 3, 1, 3,
            0, 3, 3, 0, 3, 3, 3, 3, 0, 3, 3, 1, 3,
            0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 1, 3,
            3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3,
            4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
            3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3,
            0, 3, 0, 3, 3, 3, 0, 0, 0, 3, 3, 3, 3,
        };
        memcpy(this->mapArr, mapArr_1, sizeof(this->mapArr));//复制地图路径
    }
    else if(level==2){
        int mapArr_2[8][13] =
            {
                0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
                4, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 2,
                0, 1, 0, 3, 1, 3, 3, 1, 0, 3, 1, 0, 0,
                0, 1, 3, 0, 1, 0, 0, 1, 0, 0, 1, 3, 0,
                3, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
                0, 1, 0, 3, 1, 0, 0, 1, 3, 0, 1, 0, 0,
                3, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 3, 0,
                0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
            };
        memcpy(this->mapArr, mapArr_2, sizeof(this->mapArr));
    }
    else if(level==3){        int mapArr_3[8][13] =
            {
                0, 0, 3, 2, 0, 0, 3, 0, 0, 2, 0, 0, 0,
                3, 3, 3, 1, 3, 0, 0, 0, 3, 1, 0, 3, 0,
                3, 0, 3, 1, 0, 0, 3, 0, 3, 1, 3, 0, 0,
                0, 1, 1, 1, 3, 3, 0, 3, 0, 1, 3, 0, 0,
                4, 1, 3, 0, 0, 0, 3, 0, 0, 1, 1, 1, 2,
                3, 1, 0, 0, 3, 0, 0, 3, 0, 1, 0, 3, 0,
                3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 3, 0,
                0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0,
            };
    memcpy(this->mapArr, mapArr_3, sizeof(this->mapArr));}
    else if(level==4){
        int mapArr_4[8][13] =
            {
                0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0,
                2, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 3, 0,
                0, 0, 3, 0, 3, 0, 0, 3, 1, 0, 3, 0, 0,
                4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
                3, 0, 3, 0, 0, 0, 1, 3, 0, 3, 0, 3, 0,
                2, 1, 1, 1, 0, 3, 1, 0, 0, 0, 0, 0, 0,
                0, 0, 3, 1, 1, 1, 1, 3, 0, 3, 0, 3, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            };
        memcpy(this->mapArr, mapArr_4, sizeof(this->mapArr));
    }
    map_value_to_path.insert(0, ":/new/Image/Images/Others/Scenes/water.jpg");
    map_value_to_path.insert(1, ":/new/Image/Images/Others/Scenes/land.jpg");
    map_value_to_path.insert(2, ":/new/Image/Images/Others/Scenes/land.jpg");
    map_value_to_path.insert(3, ":/new/Image/Images/Others/Scenes/grass.jpg");
    map_value_to_path.insert(4, ":/new/Image/Images/Others/Scenes/home.jpg");
    map=new mapway;
    memcpy(map->mapArr,this->mapArr,sizeof(map->mapArr));
    map->map_value_to_path=this->map_value_to_path;


}
void game::pre(int Waves){
    wave=Waves;
  /*  if(!file.open(QFile::ReadOnly|QFile::Text)){
        qDebug()<<"can't open error!";
        return;

    }

    // QJsonParseError类用于在JSON解析期间报告错误。
    QJsonParseError jsonError;
    // 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
    // 如果解析成功，返回QJsonDocument对象，否则返回null
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &jsonError);
    // 判断是否解析失败
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
        qDebug() << "Json格式错误！" << jsonError.error;
        QMessageBox * message=new QMessageBox;
        message->setWindowTitle("提示");
        message->setInformativeText("Json格式错误！");
        message->exec();
        back_to_pre();
        return;}
    QJsonObject rootObj = doc.object();
    if(level==1){//4:家，0:水上不可种格，未来可能会补荷叶 ， 3：可种格  2：出怪口  1：路径
        int mapArr_1[8][13]={
            0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 1, 2,
            3, 3, 3, 3, 0, 3, 0, 3, 3, 3, 3, 1, 3,
            0, 3, 3, 0, 3, 3, 3, 3, 0, 3, 3, 1, 3,
            0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 1, 3,
            3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3,
            4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
            3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3,
            0, 3, 0, 3, 3, 3, 0, 0, 0, 3, 3, 3, 3,
        };
        memcpy(this->mapArr, mapArr_1, sizeof(this->mapArr));//复制地图路径
    }
    else if(level==2){
        int mapArr_2[8][13] =
            {
                0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
                4, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 2,
                0, 1, 0, 3, 1, 3, 3, 1, 0, 3, 1, 0, 0,
                0, 1, 3, 0, 1, 0, 0, 1, 0, 0, 1, 3, 0,
                3, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
                0, 1, 0, 3, 1, 0, 0, 1, 3, 0, 1, 0, 0,
                3, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 3, 0,
                0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
            };
        memcpy(this->mapArr, mapArr_2, sizeof(this->mapArr));
    }
    else if(level==3){        int mapArr_3[8][13] =
            {
                0, 0, 3, 2, 0, 0, 3, 0, 0, 2, 0, 0, 0,
                3, 3, 3, 1, 3, 0, 0, 0, 3, 1, 0, 3, 0,
                3, 0, 3, 1, 0, 0, 3, 0, 3, 1, 3, 0, 0,
                0, 1, 1, 1, 3, 3, 0, 3, 0, 1, 3, 0, 0,
                4, 1, 3, 0, 0, 0, 3, 0, 0, 1, 1, 1, 2,
                3, 1, 0, 0, 3, 0, 0, 3, 0, 1, 0, 3, 0,
                3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 3, 0,
                0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0,
            };
        memcpy(this->mapArr, mapArr_3, sizeof(this->mapArr));}
    else if(level==4){
        int mapArr_4[8][13] =
            {
                0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0,
                2, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 3, 0,
                0, 0, 3, 0, 3, 0, 0, 3, 1, 0, 3, 0, 0,
                4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
                3, 0, 3, 0, 0, 0, 1, 3, 0, 3, 0, 3, 0,
                2, 1, 1, 1, 0, 3, 1, 0, 0, 0, 0, 0, 0,
                0, 0, 3, 1, 1, 1, 1, 3, 0, 3, 0, 3, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            };
        memcpy(this->mapArr, mapArr_4, sizeof(this->mapArr));
    }
    else if(level==5){
        int mapArr_5[8][13];
         memcpy(this->mapArr, mapArr_5, sizeof(this->mapArr));
    }
    memcpy(map->mapArr,this->mapArr,sizeof(map->mapArr));
    if(level!=5){
        QJsonValue hpValue = rootObj.value("hp");
         QJsonValue plantValue = rootObj.value("plants");
        QJsonValue waveValue = rootObj.value("waves");
         QJsonValue wordValue = rootObj.value("words");

         if(waveValue.isNull()||waveValue.toInt()<0||waveValue.toInt()>3){

             QMessageBox * message=new QMessageBox;
             message->setWindowTitle("提示");
             message->setInformativeText("wave格式错误！");
             message->exec();
             return;
         }

         if(hpValue.type() == QJsonValue::Array&&plantValue.type() == QJsonValue::Array&&wordValue.type() == QJsonValue::Array){
             QJsonArray hpArray = hpValue.toArray();
             QJsonArray plantArray = plantValue.toArray();
         for (int i = 0; i < 8; i++)
                 for(int j=0;j<8;j++){
                 QJsonValue hp = hpArray.at(i*8+j);
                 QJsonValue plant=plantArray.at(i*8+j);


             }
         }
         else{
             //qDebug() << "Json格式错误！" << jsonError.error;
             QMessageBox * message=new QMessageBox;
             message->setWindowTitle("提示");
             message->setInformativeText("json格式错误！");
             message->exec();
             back_to_pre();
             return;
         }
         if(wordValue.type() == QJsonValue::Array){

             QJsonArray wordArray = wordValue.toArray();
             for (int i = 0; i < 5; i++)
                 for(int j=0;j<8;j++){
                     QJsonValue WordS = wordArray.at(i);
                     int word=WordS.toInt();
                     if(word>=0)
                     words->wordamount[i]=word;

                 }
         }
         else{
             //qDebug() << "Json格式错误！" << jsonError.error;
             QMessageBox * message=new QMessageBox;
             message->setWindowTitle("提示");
             message->setInformativeText("word格式错误！");
             message->exec();
             back_to_pre();
             return;
         }
         wave=waveValue.toInt();



    }

  /*  QJsonObject rootObj = doc.object();
    QJsonValue Mapvalue=rootObj.value("map");
    if(Mapvalue.type()==QJsonValue::Object){
        QJsonObject MapObj = Mapvalue.toObject();
        QJsonValue LevelValue = MapObj.value("level");
        qDebug() << "level = " << LevelValue.toString();
        QString level=LevelValue.toString();
        if(level=="1"){}
        else if(level=="2"){}
        else if(level=="3"){}
        else if(level=="4"){}
        else{
            qDebug()<<"关卡名不合法！";
            QMessageBox * message=new QMessageBox;
            message->setWindowTitle("提示");
            message->setInformativeText("关卡名不合法！");
            message->exec();
            back_to_pre();
            return;
        }
    }
    else{
        qDebug()<<"没有指定的关卡！";
        QMessageBox * message=new QMessageBox;
        message->setWindowTitle("提示");
        message->setInformativeText("没有指定的关卡！");
        message->exec();
        back_to_pre();
            return;
    }*/

    }
void game::back_to_pre(){
    maps *w=new maps;
    w->show();
    delete this;
}
void game::paintEvent(QPaintEvent *){//这个已经不用了
   /*this->setMinimumSize(1240,840);
    this->setMaximumSize(1240,840);
    QPainter painter(this);
    for(int i=0;i<8;i++)
        for(int j=0;j<13;j++){
            painter.drawPixmap(j * blocklen+200, i * blocklen+200,blocklen,blocklen, QPixmap(map_value_to_path[mapArr[i][j]]));
        }*/
}
void game::exit_clicked(){
    timer->stop();
    ispause=1;
    Shopcard->ispause=1;
    words->ispause=1;
    if(level!=5){
    QMessageBox * message=new QMessageBox;
    message->setWindowTitle("提示");
    message->setInformativeText("是否保存存档?");
    message->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    message->setDefaultButton(QMessageBox::Yes);
    message->show();
    int ret = message->exec();
    if(ret == QMessageBox::Yes){
        SaveGames();
    }}
    MainWindow *w=new MainWindow;
    w->show();
    delete this;

}
bool game::SaveGames(){

    QJsonArray mapArray;
      QJsonArray hpArray;
    for(int i=0;i<8;i++)
        for(int j=0;j<13;j++){
            if(map->plantmap[i][j]){
                mapArray.append(map->plantmap[i][j]->name);
                 hpArray.append(map->plantmap[i][j]->hp);
            }
            else {
                mapArray.append("nothing");
                 hpArray.append(-1);
            }
        }
    QJsonArray wordsArray;
    for(int i=0;i<5;i++){
        wordsArray.append(words->wordamount[i]);
    }
    QJsonDocument doc;
    QJsonObject rootObject;
    int suntotal=Shopcard->sunTotal;
    rootObject.insert("level", level);
    rootObject.insert("waves",wave);
    rootObject.insert("sun",suntotal);
    rootObject.insert("plant", mapArray);
    rootObject.insert("hp",hpArray);
    rootObject.insert("words",wordsArray);
    // 将object设置为本文档的主要对象
    doc.setObject(rootObject);
    QFile file( "../save"+QString::number(level)+".json");
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
        QMessageBox * message=new QMessageBox;
        message->setWindowTitle("注意");
        message->setInformativeText("打开文件失败！");
        message->show();
        message->exec();
        return 0;
    } else {
        qDebug() <<"File open!";
    }
    file.write(doc.toJson());
    file.close();
    return 1;
}
void game::save_clicked(){
    timer->stop();
    ispause=1;
    Shopcard->ispause=1;
    words->ispause=1;
    map->ispause=1;
    if(SaveGames())
    { QMessageBox * message=new QMessageBox;
    message->setWindowTitle("注意");
    message->setInformativeText("存档成功!（存档不会保存已经装备的词缀，也会回退到未完成的上一波次敌人，但会保留血量和未装备的词缀）");
    message->show();
    message->exec();}
    timer->start();
    ispause=0;
    Shopcard->ispause=0;
    words->ispause=0;
    map->ispause=0;

}
void game::pause_clicked(){
    if(!ispause){
    this->pauseButton->setText("继续");
        timer->stop();
    ispause=1;
        Shopcard->ispause=1;
    words->ispause=1;
        map->ispause=1;
    }
    else{
         this->pauseButton->setText("暂停");
        timer->start();
         ispause=0;
        Shopcard->ispause=0;
         words->ispause=0;
        map->ispause=0;
    }
    QMediaPlayer *win=new QMediaPlayer;
    QAudioOutput *Win=new QAudioOutput;
    win->setAudioOutput(Win);
    win->setSource(QUrl("../Music/pause.mp3"));
    Win->setVolume(50);
    win->setLoops(QMediaPlayer::Once);
    win->play();
}
void game::addway(int level){//左下左
    if(level==1){
        Way way1(0,12,0,0);
        Way way2(0,11,3,0);
        Way way3(5,11,0,0);
        Way way4(5,0,4,0);
        way1.setNextWayPoint(way2);
        way2.setNextWayPoint(way3);
        way3.setNextWayPoint(way4);
        Way1=&way1;
        Way2=nullptr;
        Way3=nullptr;
       /* wayList.push_back(way1);
        wayList.push_back(way2);
        wayList.push_back(way3);
        wayList.push_back(way4);*/
    }
    if(level==2){
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
        way1.setNextWayPoint(way2);
        way2.setNextWayPoint(way3);
        way3.setNextWayPoint(way4);
        way4.setNextWayPoint(way5);
        way5.setNextWayPoint(way6);
        way6.setNextWayPoint(way7);
        way7.setNextWayPoint(way8);
        way8.setNextWayPoint(way9);
        way9.setNextWayPoint(way10);
       /* wayList.push_back(way1);
        wayList.push_back(way2);
        wayList.push_back(way3);
        wayList.push_back(way4);
        wayList.push_back(way5);
        wayList.push_back(way6);
        wayList.push_back(way7);
        wayList.push_back(way8);
        wayList.push_back(way9);
        wayList.push_back(way10);*/
    }
    if(level==3){
        Way way1(0,9,3,0);//下左上左
        Way way2(6,9,0,0);
        Way way3(6,1,2,0);
        Way way4(4,1,0,0);
        Way way5(4,0,4,0);
        way1.setNextWayPoint(way2);
        way2.setNextWayPoint(way3);
        way3.setNextWayPoint(way4);
        way4.setNextWayPoint(way5);
      /*  wayList.push_back(way1);
        wayList.push_back(way2);
        wayList.push_back(way3);
        wayList.push_back(way4);
        wayList.push_back(way5);*/
        Way way6(0,3,3,1);//下左下左
        Way way7(3,3,0,1);
        Way way8(3,1,3,1);
        Way way9(4,1,0,1);
        Way way10(4,0,4,1);
        way6.setNextWayPoint(way7);
        way7.setNextWayPoint(way8);
        way8.setNextWayPoint(way9);
        way9.setNextWayPoint(way10);
       /* wayList.push_back(way6);
        wayList.push_back(way7);
        wayList.push_back(way8);
        wayList.push_back(way9);
        wayList.push_back(way10);*/
        Way way11(4,12,0,2);//左下左上左
        Way way12(4,9,3,2);
        Way way13(6,9,0,2);
        Way way14(6,1,2,2);
        Way way15(4,1,0,2);
        Way way16(4,0,4,2);
        way11.setNextWayPoint(way12);
        way12.setNextWayPoint(way13);
        way13.setNextWayPoint(way14);
        way14.setNextWayPoint(way15);
        way15.setNextWayPoint(way16);
       /* wayList.push_back(way11);
        wayList.push_back(way12);
        wayList.push_back(way13);
        wayList.push_back(way14);
        wayList.push_back(way15);
        wayList.push_back(way16);*/
    }
    if(level==4){
        Way way1(3,12,0,0);//左
        Way way2(3,0,4,0);
        way1.setNextWayPoint(way2);
       /* wayList.push_back(way1);
        wayList.push_back(way2);*/
        Way way3(1,0,1,1);//右下左
        Way way4(1,8,3,1);
        Way way5(3,8,0,1);
        Way way6(3,0,4,1);
        way3.setNextWayPoint(way4);
        way4.setNextWayPoint(way5);
        way5.setNextWayPoint(way6);
      /*  wayList.push_back(way3);
        wayList.push_back(way4);
        wayList.push_back(way5);
         wayList.push_back(way6);*/
        Way way7(5,0,1,2);//右下右上左
         Way way8(5,3,3,2);
        Way way9(6,3,1,2);
         Way way10(6,6,2,2);
        Way way11(3,6,0,2);
         Way way12(2,0,4,2);
        way7.setNextWayPoint(way8);
        way8.setNextWayPoint(way9);
        way9.setNextWayPoint(way10);
        way10.setNextWayPoint(way11);
         way11.setNextWayPoint(way12);
       /* wayList.push_back(way7);
        wayList.push_back(way8);
        wayList.push_back(way9);
        wayList.push_back(way10);
        wayList.push_back(way11);
        wayList.push_back(way12);*/
    }
}
void game::check(){

    shop->playerhp=this->playerhp;
    shop->update();
    QList<QGraphicsItem *> items = scene->items();
    if(level==1){
    foreach (QGraphicsItem *item, items)
    {

            if (item->type() == Enemy::Type && item->x() <280&&item->y()>530&&item->y()<550)
        {
            playerhp--;
            qDebug()<<"-1";
                delete item;

        }
    }
    }
    if(level==2){
        foreach (QGraphicsItem *item, items)
        {

            if (item->type() == Enemy::Type && item->x() <170&&item->y()>210&&item->y()<230)
            {
                playerhp--;
                qDebug()<<"-2";
                delete item;

            }
        }
    }
    if(level==3||level==4){
        foreach (QGraphicsItem *item, items)
        {

            if (item->type() == Enemy::Type && item->x() <170&&item->y()>450&&item->y()<470)
            {
                playerhp--;
                qDebug()<<"-3";
                delete item;

            }
        }
    }

    if((level==1||level==2)&&wave==3){
        timer->stop();
        ispause=1;

        Shopcard->ispause=1;
        words->ispause=1;
        map->ispause=1;
        //qDebug()<<"YouWin!";
        QMessageBox * message=new QMessageBox;
        QMediaPlayer *win=new QMediaPlayer;
        QAudioOutput *Win=new QAudioOutput;
        win->setAudioOutput(Win);
        player.stop();
        win->setSource(QUrl("../Music/win.wav"));
        Win->setVolume(50);
        win->setLoops(QMediaPlayer::Once);
        win->play();
        message->setWindowTitle("恭喜");
        message->setInformativeText("你过关!");
        message->show();
        message->exec();
            MainWindow *w=new MainWindow;
            w->show();
            delete this;


    }
    if((level==3||level==4)&&wave==2){
        bool check=false;
        foreach (QGraphicsItem *item, items)
        {

            if (item->type() == Enemy::Type)
            {
                check=true;
            }
        }
        if(!check){
        timer->stop();
        ispause=1;

        Shopcard->ispause=1;
        words->ispause=1;
        map->ispause=1;
        QMediaPlayer *win=new QMediaPlayer;
        QAudioOutput *Win=new QAudioOutput;
        win->setAudioOutput(Win);
        player.stop();
        win->setSource(QUrl("../Music/win.wav"));
        Win->setVolume(50);
        win->setLoops(QMediaPlayer::Once);
        win->play();
        //qDebug()<<"YouWin!";
        QMessageBox * message=new QMessageBox;
        message->setWindowTitle("恭喜");
        message->setInformativeText("你过关!");
        message->show();
        message->exec();
        MainWindow *w=new MainWindow;
        w->show();
        delete this;}
    }
    if(playerhp<=0){
        timer->stop();
        ispause=1;
        Shopcard->ispause=1;
        words->ispause=1;
        map->ispause=1;
        QMediaPlayer *lose=new QMediaPlayer;
        QAudioOutput *Lose=new QAudioOutput;
        lose->setAudioOutput(Lose);
        player.stop();
        lose->setSource(QUrl("../Music/lose.wav"));
        Lose->setVolume(50);
        lose->setLoops(QMediaPlayer::Once);
        lose->play();
        QMessageBox * message=new QMessageBox;
        message->setWindowTitle("该罚");
        message->setInformativeText("僵尸吃掉了你的脑子！");
        message->show();
        message->exec();
        MainWindow *w=new MainWindow;
        w->show();
        delete this;
    }
}
void game::createZombie(){

    QPointF zombiePos;
    QTime _time= QTime::currentTime();
    srand(_time.msec()+_time.second()*1000);
    static int duringTime = 100;
    static int counter = 0;
    static int a=3;

    if(wave==3&&(level==1||level==2)){
        wave=1;

    }
    if(wave==2&&(level==3||level==4)){
        wave=1;

    }
    if(level==1){

        zombiePos = QPointF(1100, 150);
        Enemy *zombie;
        if(wave==1){
    if (++counter >= 100)
    {
        if(counter % duringTime == 0)
        {


            if (kind1 < 200)
            { zombie = new commonZombie(zombiePos,level,0);
                zombie->words=this->words;
                zombie->scene=this->scene;
                //zombie->scene=this->scene;
                zombie->setZValue(a+1);
                a++;
                //qDebug()<<"create used";
                kind1 +=10;
            scene->addItem(zombie);
            }
        }
        if(kind1==200)
            wave=2;
        }

    }
        if(wave==2){
        if(kind1<250){
                kind1+=10;
            }
        if (++counter >= 100)
        {
            if(counter % duringTime == 0)
            {


                if (kind1 >= 250&&kind1<=350)
                { zombie = new commonZombie(zombiePos,level,0);
                    zombie->scene=this->scene;
zombie->words=this->words;
                    zombie->setZValue(a+1);
                    a++;
                    scene->addItem(zombie);
                    zombie = new trashzombie(QPointF(1150,150),level,0);
                    zombie->scene=this->scene;
                    zombie->words=this->words;
                    zombie->setZValue(a+1);
                    a++;
                    scene->addItem(zombie);
                    kind1 +=10;

                }
                QList<QGraphicsItem *> items = scene->items();
                bool check=false;
                foreach (QGraphicsItem *item, items)
                {

                    if (item->type() == Enemy::Type)
                    {
                        check=true;
                    }
                }
                if(!check&&kind1==360){
                    kind1+=10;
                }
                if(kind1==370)
                    wave=3;
            }

        }
        }}
    if(level==2){

            zombiePos = QPointF(1100, 190);
            Enemy *zombie;

            if(wave==1){

                if (++counter >= 100)
                {
                    if(counter % duringTime == 0)
                    {


                        if (kind1 <=50)
                        { zombie = new commonZombie(zombiePos,level,0);
                            zombie->words=this->words;
                            zombie->scene=this->scene;

                            zombie->setZValue(a+1);
                            a++;
                            //qDebug()<<"create used";
                            kind1 +=5;
                            scene->addItem(zombie);
                        }
                        if(kind1==55)
                            kind1-=5;
                        if(kind1>=50&&kind1<=100&&kind1%10==0){
                            zombie = new trashzombie(zombiePos,level,0);
                            zombie->words=this->words;
                            zombie->scene=this->scene;
                            //zombie->scene=this->scene;
                            zombie->setZValue(a+1);
                            a++;
                            //qDebug()<<"create used";
                            kind1 +=10;
                            scene->addItem(zombie);
                        }
                    }
                    qDebug()<<kind1;
                    if(kind1>100)
                        wave=2;
                }

            }
            if(wave==2){
               // qDebug()<<kind1;
                if (++counter >= 100)
                {
                    if(counter % duringTime == 0)
                    {


                        if (kind1 >= 100&&kind1<=200){
                            if(kind1%5==0){
                        { zombie = new commonZombie(zombiePos,level,0);
                            zombie->words=this->words;
                            zombie->scene=this->scene;

                            zombie->setZValue(a+1);
                            a++;
                            scene->addItem(zombie);
                            }
                        if(kind1%10==0){
                            zombie = new trashzombie(QPointF(1150,190),level,0);
                            zombie->words=this->words;
                            zombie->scene=this->scene;
                            zombie->setZValue(a+1);
                            a++;
                            scene->addItem(zombie);
                            }
                        if(kind1%20==0){
                                zombie = new footballzombie(zombiePos,level,0);
                            zombie->words=this->words;
                                zombie->scene=this->scene;

                                zombie->setZValue(a+1);
                                a++;
                                scene->addItem(zombie);
                            }
                        kind1+=5;
                            }}
                        QList<QGraphicsItem *> items = scene->items();
                        bool check=false;
                        foreach (QGraphicsItem *item, items)
                        {

                            if (item->type() == Enemy::Type)
                            {
                                check=true;
                            }
                        }
                        if(!check&&kind1==205){
                            kind1+=10;
                        }
                        if(kind1==215)
                            wave=3;
                    }

                }
            }}
    if(level==3){
        static int counter1 = 0;
        static int counter2 = 0;
        static int counter3 = 0;
        if(wave==1){

        if (++counter1 >= 100)
        {
            if(counter1 % duringTime == 0)
            {

                zombiePos = QPointF(1100-240,150);

                Enemy *zombie;
                if (kind1 < 200)
                { zombie = new commonZombie(zombiePos,level,0);
                    zombie->words=this->words;
                    zombie->scene=this->scene;
                    //zombie->scene=this->scene;
                    zombie->setZValue(a+1);
                    a++;
                     scene->addItem(zombie);
                    if(kind1%30==0&&kind1!=0)
                    {zombie=new trashzombie(zombiePos,level,0);
                        zombie->words=this->words;
                        zombie->scene=this->scene;
                        //zombie->scene=this->scene;
                        zombie->setZValue(a+1);
                        a++;
                         scene->addItem(zombie);
                    }


                    //qDebug()<<"create used";
                    kind1 +=10;

                }
            }
        }
        if (++counter2 >= 200)
        {
            if(counter2 % duringTime == 0)
            {

                zombiePos = QPointF(1100-720,150);

                Enemy *zombie;
                if (kind2 < 100)
                { zombie = new commonZombie(zombiePos,level,1);
                    zombie->words=this->words;


                    zombie->scene=this->scene;

                    zombie->setZValue(a+1);
                    a++;
                    scene->addItem(zombie);
                    if(kind2%30==0)
                    {zombie=new trashzombie(zombiePos,level,1);
                        zombie->words=this->words;
                        zombie->scene=this->scene;
                        //zombie->scene=this->scene;
                        zombie->setZValue(a+1);
                        a++;
                        scene->addItem(zombie);
                    }
                    //qDebug()<<"create used";
                    kind2 +=10;

                }
            }
        }
        if (++counter3 >= 200)
        {
            if(counter3 % duringTime == 0)
            {

                zombiePos = QPointF(1100,150+320);

                Enemy *zombie;
                if (kind3 < 200)
                {
                    if(kind3%50==0){
                        zombie=new footballzombie(zombiePos,level,2);
                        zombie->words=this->words;
                        zombie->scene=this->scene;
                        //zombie->scene=this->scene;
                        zombie->setZValue(a+1);
                        a++;
                        scene->addItem(zombie);
                    }
                    if(kind3%30==0&&kind3!=0){
                        zombie=new trashzombie(zombiePos,level,2);
                        zombie->words=this->words;
                        zombie->scene=this->scene;
                        //zombie->scene=this->scene;
                        zombie->setZValue(a+1);
                        a++;
                        scene->addItem(zombie);
                    }
                    //qDebug()<<"create used";
                    kind3 +=10;

                }
            }
        }

        if(kind1==200&&kind2==100&&kind3==200)
            wave=2;
        }

    }
    if(level==4){//左，右下左，右下右上左
        static int counter1 = 0;
        static int counter2 = 0;
        static int counter3 = 0;
        if(wave==1){

            if (++counter1 >= 100)
            {
                if(counter1 % duringTime == 0)
                {

                    zombiePos = QPointF(1100,150+240);

                    Enemy *zombie;
                    if (kind1 < 200)
                    { zombie = new commonZombie(zombiePos,level,0);
                        zombie->words=this->words;
                        zombie->scene=this->scene;
                        //zombie->scene=this->scene;
                        zombie->setZValue(a+1);
                        a++;
                        scene->addItem(zombie);
                        if(kind1%30==0&&kind1!=0)
                        {zombie=new trashzombie(zombiePos,level,0);
                            zombie->words=this->words;
                            zombie->scene=this->scene;
                            //zombie->scene=this->scene;
                            zombie->setZValue(a+1);
                            a++;
                            scene->addItem(zombie);
                        }


                        //qDebug()<<"create used";
                        kind1 +=10;

                    }
                }
            }
            if (++counter2 >= 200)
            {
                if(counter2 % duringTime == 0)
                {

                    zombiePos = QPointF(1100-960,150+80);

                    Enemy *zombie;
                    if (kind2 < 100)
                    { zombie = new commonZombie(zombiePos,level,1);
                        zombie->words=this->words;


                        zombie->scene=this->scene;

                        zombie->setZValue(a+1);
                        a++;
                        scene->addItem(zombie);
                        if(kind2%30==0&&kind2!=0)
                        {zombie=new trashzombie(zombiePos,level,1);
                            zombie->words=this->words;
                            zombie->scene=this->scene;
                            //zombie->scene=this->scene;
                            zombie->setZValue(a+1);
                            a++;
                            scene->addItem(zombie);
                        }
                        if(kind2%50==0&&kind2!=0){
                            zombie=new footballzombie(zombiePos,level,1);
                            zombie->words=this->words;
                            zombie->scene=this->scene;
                            //zombie->scene=this->scene;
                            zombie->setZValue(a+1);
                            a++;
                            scene->addItem(zombie);
                        }
                        //qDebug()<<"create used";
                        kind2 +=10;

                    }
                }
            }
            if (++counter3 >= 200)
            {
                if(counter3 % duringTime == 0)
                {

                    zombiePos = QPointF(1100-960,150+400);

                    Enemy *zombie;
                    if (kind3 < 200)
                    {
                        zombie = new commonZombie(zombiePos,level,2);
                        zombie->words=this->words;
                        zombie->scene=this->scene;
                        //zombie->scene=this->scene;
                        zombie->setZValue(a+1);
                        a++;
                        scene->addItem(zombie);
                        if(kind3%50==0){
                            zombie=new footballzombie(zombiePos,level,2);
                            zombie->words=this->words;
                            zombie->scene=this->scene;
                            //zombie->scene=this->scene;
                            zombie->setZValue(a+1);
                            a++;
                            scene->addItem(zombie);
                        }
                        //qDebug()<<"create used";
                        kind3 +=10;

                    }
                }
            }

            if(kind1==200&&kind2==100&&kind3==200)
                wave=2;
        }
    }
}
