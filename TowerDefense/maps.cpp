#include "maps.h"
#include "ui_maps.h"
#include"game.h"
#include<QAudioOutput>
#include<mainwindow.h>
#include <QJsonObject> // { }
#include <QJsonArray> // [ ]
#include <QJsonDocument> // 解析Json
#include <QJsonValue> // int float double bool null { } [ ]
#include <QJsonParseError>
#include<QFile>
#include<QDir>
#include<QFileDialog>
#include"caltrop.h"
#include"cherrybomb.h"
#include"chomper.h"
#include"peashooter.h"
#include"repeater.h"
#include"snowpea.h"
#include"wallnut.h"
maps::maps(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::maps)
{
    QPalette pal =this->palette();
    pal.setBrush(QPalette::Window,QBrush(QPixmap(":/new/Image/Images/Others/controller/chooseseeds.jpg")));
    setPalette(pal);
    this->setWindowIcon(QIcon(":/new/Image/Images/Others/Scenes/icon.png"));
    this->setMinimumSize(840,600);
    this->setMaximumSize(840,600);
    this->returnbutton=new QPushButton("返回",this);
    MediaPlayer=new QMediaPlayer(this);
    QAudioOutput * output=new QAudioOutput(this);
    MediaPlayer->setAudioOutput(output);
    output->setVolume(50);
    MediaPlayer->setSource(QUrl("../Music/Laura Shigihara - Faster [mqms].mp3"));//qq音乐有保护机制，.qrc无法读取，只能采取绝对路径，请将Music文件copy到编译运行后和debug和release同级的文件夹后方可听到音乐
    MediaPlayer->play();
    returnbutton->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    this->returnbutton->setGeometry(600,0,200,50);
    connect(returnbutton,SIGNAL(clicked(bool)),this,SLOT(returnbutton_clicked()));
    this->level1=new QPushButton("第一关",this);
    this->level2=new QPushButton("第二关",this);
    this->level3=new QPushButton("第三关",this);
    this->level4=new QPushButton("第四关",this);
    this->load=new QPushButton("加载存档",this);
    this->level1->setGeometry(0,100,100,50);
    this->level2->setGeometry(150,100,100,50);
    this->level3->setGeometry(300,100,100,50);
    this->level4->setGeometry(450,100,100,50);
    this->load->setGeometry(0,250,200,50);
    level1->setStyleSheet("background-image:url(:/new/Image/Images/Others/Scenes/getzombies.jpg)");
    level2->setStyleSheet("background-image:url(:/new/Image/Images/Others/Scenes/getzombies.jpg)");
    level3->setStyleSheet("background-image:url(:/new/Image/Images/Others/Scenes/getzombies.jpg)");
    level4->setStyleSheet("background-image:url(:/new/Image/Images/Others/Scenes/getzombies.jpg)");
    load->setStyleSheet("background-image:url(:/new/Image/Images/Others/Scenes/getzombies.jpg)");
    ui->setupUi(this);
    connect(level1,SIGNAL(clicked(bool)),this,SLOT(level1_clicked()));
    connect(level2,SIGNAL(clicked(bool)),this,SLOT(level2_clicked()));
    connect(level3,SIGNAL(clicked(bool)),this,SLOT(level3_clicked()));
    connect(level4,SIGNAL(clicked(bool)),this,SLOT(level4_clicked()));
    connect(load,SIGNAL(clicked(bool)),this,SLOT(load_clicked()));

}

maps::~maps()
{
    delete ui;
}
void maps::returnbutton_clicked(){
    MediaPlayer->stop();
    delete this;
    MainWindow *w=new MainWindow;
    w->show();
    //delete掉本窗体

}
void maps::level1_clicked(){
    MediaPlayer->stop();
    delete this;
    game *w=new game(nullptr,1);
    w->show();

}
void maps::level2_clicked(){
    MediaPlayer->stop();
    delete this;
    game *w=new game(nullptr,2);
    w->show();
}
void maps::level3_clicked(){
    MediaPlayer->stop();
    delete this;
    game *w=new game(nullptr,3);
    w->show();
}
void maps::level4_clicked(){
    MediaPlayer->stop();
    game *w=new game(nullptr,4);
    w->show();
    delete this;
}
void maps::load_clicked(){
    load_from_file();
    //delete this;
}
void maps::load_from_file(){

    QString curPath=QDir::currentPath();//获取当前程序目录路径
    QString DlgTitle=("打开一个文件");
    QString filter="JSON 文件 (*.json)";
    QString aFileName=QFileDialog::getOpenFileName(this,DlgTitle,curPath,filter);
    if(aFileName.isEmpty()){
        return;
    }
    QFile file(aFileName);
    if(!file.exists()){
        throw false;
    }
    int level;
    QJsonParseError jsonError;
    // 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
    // 如果解析成功，返回QJsonDocument对象，否则返回null

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        qDebug()<<false;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &jsonError);
    // 判断是否解析失败
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
        qDebug() << "Json格式错误！" << jsonError.error;
        QMessageBox * message=new QMessageBox;
        message->setWindowTitle("提示");
        message->setInformativeText("打开JSON格式错误！");
        message->exec();
        return;}
    QJsonObject rootObj = doc.object();

    QJsonValue levelValue = rootObj.value("level");

    if(levelValue.isNull()||levelValue.toInt()<=0||levelValue.toInt()>5){
        qDebug() << "没有指定的level!请检查是否有level:,且数值在1~5之间！" << jsonError.error;
        QMessageBox * message=new QMessageBox;
        message->setWindowTitle("提示");
        message->setInformativeText("没有指定的level!请检查是否有level:,且数值在1~5之间！");
        message->exec();
        return;
    }
    level=levelValue.toInt();

    game *w=new game(nullptr,level);
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
        memcpy(w->mapArr, mapArr_1, sizeof(w->mapArr));//复制地图路径
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
        memcpy(w->mapArr, mapArr_2, sizeof(w->mapArr));
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
        memcpy(w->mapArr, mapArr_3, sizeof(w->mapArr));}
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
        memcpy(w->mapArr, mapArr_4, sizeof(w->mapArr));
    }
    else if(level==5){
        int mapArr_5[8][13];
         QJsonValue mapValue = rootObj.value("map");
        if(mapValue.type() == QJsonValue::Array){
             QJsonArray MapArray = mapValue.toArray();
        for (int i = 0; i < 8; i++)
            for(int j=0;j<13;j++){
                QJsonValue Map=MapArray.at(i*13+j);
                if(Map.toInt()>=0&&Map.toInt()<=4)
                mapArr_5[i][j]=Map.toInt();
                else{
                    QMessageBox * message=new QMessageBox;
                    message->setWindowTitle("提示");
                    message->setInformativeText("地图格子格式错误！");
                    message->exec();
                    return;
                }
            }
        }
        else{
            QMessageBox * message=new QMessageBox;
            message->setWindowTitle("提示");
            message->setInformativeText("map格式错误！");
            message->exec();
            return;
        }
        memcpy(w->mapArr, mapArr_5, sizeof(w->mapArr));}

    memcpy(w->map->mapArr,w->mapArr,sizeof(w->map->mapArr));
    if(level!=5){
        QJsonValue hpValue = rootObj.value("hp");
        QJsonValue plantValue = rootObj.value("plant");
        QJsonValue waveValue = rootObj.value("waves");
        QJsonValue wordValue = rootObj.value("words");
        QJsonValue sunValue=rootObj.value("sun");
        qDebug()<<plantValue.type()<<wordValue.type()<<QJsonValue::Array;
        if(waveValue.isNull()||waveValue.toInt()<0||waveValue.toInt()>3){

            QMessageBox * message=new QMessageBox;
            message->setWindowTitle("提示");
            message->setInformativeText("wave格式错误！");
            message->exec();
            return;
        }
        if(sunValue.isNull()||sunValue.toInt()>6000||sunValue.toInt()<0){

            QMessageBox * message=new QMessageBox;
            message->setWindowTitle("提示");
            message->setInformativeText("sun格式错误！");
            message->exec();
            return;
        }

        if(hpValue.type() == QJsonValue::Array&&plantValue.type() == QJsonValue::Array&&plantValue.type() == QJsonValue::Array){
            QJsonArray hpArray = hpValue.toArray();
            QJsonArray plantArray = plantValue.toArray();
            for (int i = 0; i < 8; i++)
                for(int j=0;j<13;j++){
                     QPointF plantPos(200+80*j-30, 200+80*i-60);
                    QJsonValue hp = hpArray.at(i*13+j);
                    QJsonValue plant=plantArray.at(i*13+j);
                    if(plant.toString()!="nothing")
                    {
                        qDebug()<<i<<j;
                        int HP=hp.toInt();
                        if(plant.toString()=="Caltrop"){
                            w->map->plantmap[i][j]=new Caltrop(plantPos);
                            w->map->plantmap[i][j]->setZValue(j);//z值越大就在越顶层
                            w->map->plantmap[i][j]->scene=w->scene;
                            w->map->plantmap[i][j]->Shopcard=w->Shopcard;
                            w->map->plantmap[i][j]->hp=HP;
                            w->scene->addItem(w->map->plantmap[i][j]);

                        }
                        if(plant.toString()=="CherryBomb"){
                            w->map->plantmap[i][j]=new CherryBomb(plantPos);
                            w->map->plantmap[i][j]->setZValue(j);//z值越大就在越顶层
                            w->map->plantmap[i][j]->scene=w->scene;
                            w->map->plantmap[i][j]->Shopcard=w->Shopcard;
                            w->map->plantmap[i][j]->hp=HP;
                            w->scene->addItem(w->map->plantmap[i][j]);
                        }
                        if(plant.toString()=="Chomper"){
                            w->map->plantmap[i][j]=new Chomper(plantPos);
                            w->map->plantmap[i][j]->setZValue(j);//z值越大就在越顶层
                            w->map->plantmap[i][j]->scene=w->scene;
                            w->map->plantmap[i][j]->Shopcard=w->Shopcard;
                            w->map->plantmap[i][j]->hp=HP;
                            w->scene->addItem(w->map->plantmap[i][j]);
                        }
                        if(plant.toString()=="Peashooter"){
                            w->map->plantmap[i][j]=new PeaShooter(plantPos);
                            w->map->plantmap[i][j]->setZValue(j);//z值越大就在越顶层
                            w->map->plantmap[i][j]->scene=w->scene;
                            w->map->plantmap[i][j]->Shopcard=w->Shopcard;
                            w->map->plantmap[i][j]->hp=HP;
                            w->scene->addItem(w->map->plantmap[i][j]);
                        }
                        if(plant.toString()=="Repeater"){
                            w->map->plantmap[i][j]=new repeater(plantPos);
                            w->map->plantmap[i][j]->setZValue(j);//z值越大就在越顶层
                            w->map->plantmap[i][j]->scene=w->scene;
                            w->map->plantmap[i][j]->Shopcard=w->Shopcard;
                            w->map->plantmap[i][j]->hp=HP;
                            w->scene->addItem(w->map->plantmap[i][j]);
                        }
                        if(plant.toString()=="Snowpea"){
                            w->map->plantmap[i][j]=new SnowPea(plantPos);
                            w->map->plantmap[i][j]->setZValue(j);//z值越大就在越顶层
                            w->map->plantmap[i][j]->scene=w->scene;
                            w->map->plantmap[i][j]->Shopcard=w->Shopcard;
                            w->map->plantmap[i][j]->hp=HP;
                            w->scene->addItem(w->map->plantmap[i][j]);
                        }
                        if(plant.toString()=="Wallnut"){
                            w->map->plantmap[i][j]=new Wallnut(plantPos);
                            w->map->plantmap[i][j]->setZValue(j);//z值越大就在越顶层
                            w->map->plantmap[i][j]->scene=w->scene;
                            w->map->plantmap[i][j]->Shopcard=w->Shopcard;
                            w->map->plantmap[i][j]->hp=HP;
                            w->scene->addItem(w->map->plantmap[i][j]);
                        }

                }

                }
        }
        else{
            //qDebug() << "Json格式错误！" << jsonError.error;
            QMessageBox * message=new QMessageBox;
            message->setWindowTitle("提示");
            message->setInformativeText("hp格式错误！");
            message->exec();
            return;
        }
        if(wordValue.type() == QJsonValue::Array){

            QJsonArray wordArray = wordValue.toArray();
            for (int i = 0; i < 5; i++)
                for(int j=0;j<8;j++){
                    QJsonValue WordS = wordArray.at(i);
                    int word=WordS.toInt();
                   // qDebug()<<word;
                    if(word>=0)
                        w->words->wordamount[i]=word;

                }
        }
        else{
            //qDebug() << "Json格式错误！" << jsonError.error;
            QMessageBox * message=new QMessageBox;
            message->setWindowTitle("提示");
            message->setInformativeText("word格式错误！");
            message->exec();
            return;
        }

        w->pre(waveValue.toInt());
        w->Shopcard->sunTotal=sunValue.toInt();
    }
    w->show();
   delete this;

}
