#include "menu.h"
#include "ui_menu.h"
#include"mainwindow.h"
#include<QMediaPlayer>
#include<QAudioOutput>
menu::menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    this->setWindowIcon(QIcon(":/new/Image/Images/Others/Scenes/icon.png"));
    this->setMinimumSize(840,840);
    this->setMaximumSize(840,840);
    this->returnbutton=new QPushButton("返回",this);
    this->returnbutton->setGeometry(640,0,200,70);
    MenuMediaPlayer=new QMediaPlayer(this);
    QAudioOutput * output=new QAudioOutput(this);
    MenuMediaPlayer->setAudioOutput(output);
    output->setVolume(50);
    MenuMediaPlayer->setLoops(QMediaPlayer::Infinite);
    MenuMediaPlayer->setSource(QUrl("../Music/Laura Shigihara - Faster [mqms].mp3"));//qq音乐有保护机制，.qrc无法读取，只能采取绝对路径，请将Music文件copy到编译运行后和debug和release同级的文件夹后方可听到音乐
    MenuMediaPlayer->play();
    returnbutton->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    this->returnbutton->setGeometry(600,0,200,50);
    connect(returnbutton,SIGNAL(clicked(bool)),this,SLOT(returnbutton_clicked()));
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}
void menu::returnbutton_clicked(){
    MenuMediaPlayer->stop();
    MainWindow *w=new MainWindow;
    w->show();
    //delete掉本窗体
    delete this;
}
