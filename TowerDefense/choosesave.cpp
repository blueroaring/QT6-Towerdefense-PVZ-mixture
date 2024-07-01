#include "choosesave.h"
#include "ui_choosesave.h"
#include"mainwindow.h"
#include<QFile>
#include<QLabel>
choosesave::choosesave(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::choosesave)
{


    this->setWindowTitle(QStringLiteral("选择你想要存的文件"));
    this->setWindowIcon(QIcon(":/new/Image/Images/Others/Scenes/icon.png"));//设置窗口图标
    this->setMinimumSize(1000,1000);
    this->setMaximumSize(1000,1000);//设置开始窗口大小，禁止扩大
    this->level1 = new QPushButton("关卡1",this);
    this->level2 = new QPushButton("关卡2",this);//选关存档
    this->level3=new QPushButton("关卡3",this);
    this->level4 = new QPushButton("关卡4",this);
    level1->setFont(QFont("宋体", 30));//设置字体大小
    level2->setFont(QFont("宋体", 30));
    level3->setFont(QFont("宋体", 30));
    level4->setFont(QFont("宋体", 30));
    this->level1->setGeometry(0,100,400,400);
    level1->setStyleSheet("border-image:url(:/levelimage/Images/Others/Scenes/level1.png);");//设置背景图为关卡图片预览
    this->level2->setGeometry(500,100,400,400);
    level2->setStyleSheet("border-image:url(:/levelimage/Images/Others/Scenes/level2.png);");
    this->level3->setGeometry(0,600,400,400);
    level3->setStyleSheet("border-image:url(:/levelimage/Images/Others/Scenes/level3.png);");
    this->level4->setGeometry(500,600,400,400);
    level4->setStyleSheet("border-image:url(:/levelimage/Images/Others/Scenes/level4.png);");

    connect(level1,SIGNAL(clicked(bool)),this,SLOT(level1_clicked()));
    connect(level2,SIGNAL(clicked(bool)),this,SLOT(level2_clicked()));
    connect(level3,SIGNAL(clicked(bool)),this,SLOT(level3_clicked()));
    connect(level4,SIGNAL(clicked(bool)),this,SLOT(level4_clicked()));
    ui->setupUi(this);
}

choosesave::~choosesave()
{
    delete ui;
}
void choosesave::level1_clicked(){

    QJsonArray mapArray;//存入level(5),只能观看不能玩，存入地图数据（可修改）

    int mapArr[8][13]={
        0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 1, 2,
        3, 3, 3, 3, 0, 3, 0, 3, 3, 3, 3, 1, 3,
        0, 3, 3, 0, 3, 3, 3, 3, 0, 3, 3, 1, 3,
        0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 1, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3,
        4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
        3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3,
        0, 3, 0, 3, 3, 3, 0, 0, 0, 3, 3, 3, 3,
    };
    QJsonObject rootObject;
    for(int i=0;i<8;i++)
        for(int j=0;j<13;j++){
            mapArray.append(mapArr[i][j]);
        }

    QJsonDocument doc;
    rootObject.insert("level", 5);//level
    rootObject.insert("map", mapArray);//map
    // 将object设置为本文档的主要对象
    doc.setObject(rootObject);
    QFile file( "../save5.json");//存入save5.json文件
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
        QMessageBox * message=new QMessageBox;
        message->setWindowTitle("注意");
        message->setInformativeText("打开文件失败！");
        message->show();
        message->exec();
        MainWindow *w=new MainWindow;
        w->show();
        delete this;
    } else {
        qDebug() <<"File open!";
    }
    file.write(doc.toJson());
    file.close();
    QMessageBox * message=new QMessageBox;
    message->setWindowTitle("注意");
    message->setInformativeText("获取存档成功！");
    message->show();
    message->exec();
    MainWindow *w=new MainWindow;
    w->show();
    delete this;

}
void choosesave::level2_clicked(){

    QJsonArray mapArray;

    int mapArr[8][13]={
        0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
        4, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 2,
        0, 1, 0, 3, 1, 3, 3, 1, 0, 3, 1, 0, 0,
        0, 1, 3, 0, 1, 0, 0, 1, 0, 0, 1, 3, 0,
        3, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
        0, 1, 0, 3, 1, 0, 0, 1, 3, 0, 1, 0, 0,
        3, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 3, 0,
        0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
    };
    QJsonObject rootObject;
    for(int i=0;i<8;i++)
        for(int j=0;j<13;j++){
            mapArray.append(mapArr[i][j]);
        }


    QJsonDocument doc;
    rootObject.insert("level", 5);
    rootObject.insert("map", mapArray);
    // 将object设置为本文档的主要对象
    doc.setObject(rootObject);
    QFile file( "../save5.json");
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
        QMessageBox * message=new QMessageBox;
        message->setWindowTitle("注意");
        message->setInformativeText("打开文件失败！");
        message->show();
        message->exec();
        MainWindow *w=new MainWindow;
        w->show();
        delete this;
    } else {
        qDebug() <<"File open!";
    }
    file.write(doc.toJson());
    file.close();
    QMessageBox * message=new QMessageBox;
    message->setWindowTitle("注意");
    message->setInformativeText("获取存档成功！");
    message->show();
    message->exec();
    MainWindow *w=new MainWindow;
    w->show();
    delete this;
}
void choosesave::level3_clicked(){

    QJsonArray mapArray;

    int mapArr[8][13]={
        0, 0, 3, 2, 0, 0, 3, 0, 0, 2, 0, 0, 0,
        3, 3, 3, 1, 3, 0, 0, 0, 3, 1, 0, 3, 0,
        3, 0, 3, 1, 0, 0, 3, 0, 3, 1, 3, 0, 0,
        0, 1, 1, 1, 3, 3, 0, 3, 0, 1, 3, 0, 0,
        4, 1, 3, 0, 0, 0, 3, 0, 0, 1, 1, 1, 2,
        3, 1, 0, 0, 3, 0, 0, 3, 0, 1, 0, 3, 0,
        3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 3, 0,
        0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0,
    };
    QJsonObject rootObject;
    for(int i=0;i<8;i++)
        for(int j=0;j<13;j++){
            mapArray.append(mapArr[i][j]);
        }


    QJsonDocument doc;
    rootObject.insert("level", 5);
    rootObject.insert("map", mapArray);
    // 将object设置为本文档的主要对象
    doc.setObject(rootObject);
    QFile file( "../save5.json");
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
        QMessageBox * message=new QMessageBox;
        message->setWindowTitle("注意");
        message->setInformativeText("打开文件失败！");
        message->show();
        message->exec();
        MainWindow *w=new MainWindow;
        w->show();
        delete this;
    } else {
        qDebug() <<"File open!";
    }
    file.write(doc.toJson());
    file.close();
    QMessageBox * message=new QMessageBox;
    message->setWindowTitle("注意");
    message->setInformativeText("获取存档成功！");
    message->show();
    message->exec();
    MainWindow *w=new MainWindow;
    w->show();
    delete this;
}
void choosesave::level4_clicked(){

    QJsonArray mapArray;

    int mapArr[8][13]={
        0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 3, 0,
        0, 0, 3, 0, 3, 0, 0, 3, 1, 0, 3, 0, 0,
        4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        3, 0, 3, 0, 0, 0, 1, 3, 0, 3, 0, 3, 0,
        2, 1, 1, 1, 0, 3, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 3, 1, 1, 1, 1, 3, 0, 3, 0, 3, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    QJsonObject rootObject;
    for(int i=0;i<8;i++)
        for(int j=0;j<13;j++){
            mapArray.append(mapArr[i][j]);
        }

    QJsonDocument doc;
    rootObject.insert("level", 5);
    rootObject.insert("map", mapArray);
    // 将object设置为本文档的主要对象
    doc.setObject(rootObject);
    QFile file( "../save5.json");
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
        QMessageBox * message=new QMessageBox;
        message->setWindowTitle("注意");
        message->setInformativeText("打开文件失败！");
        message->show();
        message->exec();
        MainWindow *w=new MainWindow;
        w->show();
        delete this;
    } else {
        qDebug() <<"File open!";
    }
    file.write(doc.toJson());
    file.close();
    QMessageBox * message=new QMessageBox;
    message->setWindowTitle("注意");
    message->setInformativeText("获取存档成功！");
    message->show();
    message->exec();
    MainWindow *w=new MainWindow;
    w->show();
    delete this;
}
