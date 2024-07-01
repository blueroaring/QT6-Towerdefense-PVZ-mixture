#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"help.h"
#include"menu.h"
#include"maps.h"
#include"game.h"
#include <QDir>
#include <QVector>
#include <iostream>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGuiApplication>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QList>
#include <QPalette>
#include <QMediaPlayer>
#include <QGridLayout>
#include <QString>
#include <QDesktopServices>
#include <QUrl>
#include<QMediaPlayer>
#include<QAudioOutput>
#include<QPixmap>
#include<QMessageBox>
#include<QPaintEvent>
#include"choosesave.h"
QFont font1("Times New Roman",20,QFont::Bold,false);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setMouseTracking(true);//允许鼠标获取
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("GHW的魔改版PVZ"));//窗口名称
    this->setWindowIcon(QIcon(":/new/Image/Images/Others/Scenes/icon.png"));//设置窗口图标
    this->setMinimumSize(840,840);
    this->setMaximumSize(840,840);//设置开始窗口大小，禁止扩大
    this->setStyleSheet("border-image:url(:/new/Image/Images/Others/controller/Options.png)");//设置界面图片
    MainWindowplayer=new QMediaPlayer(this);
    QAudioOutput * MainWindowoutput=new QAudioOutput(this);//放歌
    MainWindowplayer->setAudioOutput(MainWindowoutput);
    MainWindowoutput->setVolume(50);
    MainWindowplayer->setSource(QUrl("../Music/Laura Shigihara - Zombies on Your Lawn [mqms2].mp3"));//qq音乐有保护机制，.qrc无法读取，只能采取绝对路径，请将Music文件copy到编译运行后和debug和release同级的文件夹后方可听到音乐
    MainWindowplayer->play();
    MainWindowplayer->setLoops(QMediaPlayer::Infinite);
    this->startButton = new QPushButton("开始",this);//从第一关开始（或者之前通过的最高关卡）
    this->optionButton = new QPushButton("选关",this);//选关
    this->menuButton=new QPushButton("图鉴",this);//介绍植物和僵尸，也可能有升级系统
    this->helpButton = new QPushButton("帮助",this);//玩法介绍
    this->exitButton = new QPushButton("退出",this);//退出游戏
    this->level5Button=new QPushButton("存地图",this);
    this->startButton->setGeometry(300,190,250,70);
    startButton->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    this->optionButton->setGeometry(300,270,250,70);
    optionButton->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    this->menuButton->setGeometry(300,350,250,70);
    menuButton->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    this->helpButton->setGeometry(300,430,250,70);
    helpButton->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    this->exitButton->setGeometry(300,510,250,70);
    exitButton->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    this->level5Button->setGeometry(300,590,250,70);
    level5Button->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    connect(exitButton,SIGNAL(clicked(bool)),this,SLOT(exit_game_clicked()));//退出按钮
    connect(helpButton,SIGNAL(clicked(bool)),this,SLOT(play_rules_clicked()));//规则按钮
    connect(menuButton,SIGNAL(clicked(bool)),this,SLOT(menu_clicked()));//图鉴按钮
    connect(optionButton,SIGNAL(clicked(bool)),this,SLOT(choosegame_clicked()));//选关界面
    connect(startButton,SIGNAL(clicked(bool)),this,SLOT(newstartgame_clicked()));//直接开始新游戏
    connect(level5Button,SIGNAL(clicked(bool)),this,SLOT(level5_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::exit_game_clicked(){
    QMessageBox * message=new QMessageBox;
    message->setWindowTitle("提示");
    message->setInformativeText("确实要退出吗?");
    message->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    message->setDefaultButton(QMessageBox::Yes);
    message->show();
    int ret = message->exec();
    if(ret == QMessageBox::Yes){
        close();
    }
    else{
        message->close();
    }
}
void MainWindow::play_rules_clicked(){

    MainWindowplayer->stop();
    help *w=new help;
    this->close();
    w->show();

}
void MainWindow::menu_clicked(){
    MainWindowplayer->stop();
    menu *w =new menu;
    this->close();
    w->show();

}
void MainWindow::choosegame_clicked(){
    MainWindowplayer->stop();
    maps *w =new maps;
    this->close();
    w->show();
}
void MainWindow::newstartgame_clicked(){
    MainWindowplayer->stop();
    game *w=new game(nullptr,1);
    this->close();
    w->show();
}
void MainWindow::level5_clicked(){
    MainWindowplayer->stop();
    a=new choosesave;
    this->close();
    a->show();




}
