#include "help.h"
#include "ui_help.h"
#include"mainwindow.h"
#include<QAudioOutput>
#include<QMainWindow>
#include<QPalette>
void help::returnbutton_clicked(){

    helpMediaPlayer->stop();
    MainWindow *w=new MainWindow;
    w->show();
    //delete掉本窗体
    delete this;
}
help::help(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::help)
{
    page=1;
    finalpage=12;
    label=new QLabel(this);
    Page=new QLabel(this);
    pix=new QLabel(this);
    this->label->setWordWrap(true);//自动换行
    label->setText("免责声明：他人代码仅用于借鉴思想，代码都是自己重构逻辑自己写的！");
    label->resize(400,800);
    label->move(400,-150);
    pix->resize(400,300);
    pix->move(0,200);
    Page->resize(200,50);
    Page->move(400,530);
    QPixmap pixmap;

    pixmap.load(":/help/Images/Others/controller/envelope/ZombieNote1.png");
    pix->setScaledContents(true);
    pixmap.scaled(pix->size());

    pix->setPixmap(pixmap);
    Page->setText(QString::number(page)+"/"+QString::number(finalpage));
    QFont ft;
    ft.setPointSize(20);
    label->setFont(ft);
    QPalette pal =this->palette();
    pal.setBrush(QPalette::Window,QBrush(QPixmap(":/new/Image/Images/Others/controller/help.jpg")));
    setPalette(pal);
    this->setWindowIcon(QIcon(":/new/Image/Images/Others/Scenes/icon.png"));
    this->setMinimumSize(840,600);
    this->setMaximumSize(840,600);
    this->returnbutton=new QPushButton("返回",this);
    this->nextbutton=new QPushButton("下一页",this);
    helpMediaPlayer=new QMediaPlayer(this);
    QAudioOutput * helpoutput=new QAudioOutput(this);
    helpMediaPlayer->setAudioOutput(helpoutput);
    helpMediaPlayer->setLoops(QMediaPlayer::Infinite);
    helpoutput->setVolume(50);
    helpMediaPlayer->setSource(QUrl("../Music/Laura Shigihara - Faster [mqms].mp3"));//qq音乐有保护机制，.qrc无法读取，只能采取绝对路径，请将Music文件copy到编译运行后和debug和release同级的文件夹后方可听到音乐
    helpMediaPlayer->play();
    returnbutton->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    nextbutton->setStyleSheet("background-image:url(:/new/Image/Images/Others/controller/menulist/pushbutton.png);");
    this->returnbutton->setGeometry(600,0,200,50);
    this->nextbutton->setGeometry(0,0,200,50);
    connect(nextbutton,SIGNAL(clicked(bool)),this,SLOT(nextpage_clicked()));
    connect(returnbutton,SIGNAL(clicked(bool)),this,SLOT(returnbutton_clicked()));
    ui->setupUi(this);

}

help::~help()
{
    delete ui;
}
void help::nextpage_clicked(){
    page++;

    if(page==2){
            label->setText("这是地图，你只需要点击关卡选择，选择一个关卡，然后等着僵尸进屋就可以了！（ps:直接开始新游戏可以进入第一关偶）");
        QPixmap pixmap;

        pixmap.load(":/levelimage/Images/Others/Scenes/level4.png");
            pix->setScaledContents(true);
        pixmap.scaled(pix->size());

        pix->setPixmap(pixmap);
        Page->setText(QString::number(page)+"/"+QString::number(finalpage));
    }
    if(page==3){
        label->setText("这是你的选卡槽，你有七种植物可供选择！特性请自己探索吧！（ps:因为图鉴没做完），点击卡槽再点击地图格子即可种植。\n你的阳光数初始是150（为什么这里是5000？答：开发者模式），每隔一定时间，阳光会增加50。");
        pix->resize(400,100);
        QPixmap pixmap;

        pixmap.load(":/help/Images/a1.png");
        pix->setScaledContents(true);
        pixmap.scaled(pix->size());

        pix->setPixmap(pixmap);
        Page->setText(QString::number(page)+"/"+QString::number(finalpage));
    }
    if(page==4){
        label->setText("这是你的工具栏！退出会询问你是否要存档，存档会实时存档（之前的存档会被覆盖欧，请及时改文件名），暂停可以暂停游戏，再次点击可以继续游戏；铲子可以铲除已经种植的植物。");
        pix->resize(200,400);
        QPixmap pixmap;

        pixmap.load(":/help/Images/a2.png");
        pix->setScaledContents(true);
        pixmap.scaled(pix->size());

        pix->setPixmap(pixmap);
        Page->setText(QString::number(page)+"/"+QString::number(finalpage));
    }
    if(page==5){
        label->setText("关于存档（1）：点击选关->加载存档，选择save+i类型的文件（不限制文件名，但是必须是通过存档生成的文件，否则会报错，默认生成文件名就叫save+i）,即可加载存档。可以修改植物的hp和名字（不能违规）。");
        pix->resize(400,300);
        QPixmap pixmap;

        pixmap.load(":/help/Images/a3.png");
        pix->setScaledContents(true);
        pixmap.scaled(pix->size());

        pix->setPixmap(pixmap);
        Page->setText(QString::number(page)+"/"+QString::number(finalpage));
    }
    if(page==6){
        label->setText("关于存档（2）：点击存地图，选择想要存的地图，即可存一个观赏地图（不可玩），可以通过修改地图并加载存档生成其他观赏地图。");
        pix->resize(400,300);
        QPixmap pixmap;

        pixmap.load(":/help/Images/a4.png");
        pix->setScaledContents(true);
        pixmap.scaled(pix->size());

        pix->setPixmap(pixmap);
        Page->setText(QString::number(page)+"/"+QString::number(finalpage));
    }
    if(page==7){

        pix->hide();
        label->setText("植物名称：Peashooter豌豆射手，Repeater双发射手，Snowpea寒冰射手，Chomper大嘴花，Caltrop地刺，Cherrybomb樱桃炸弹，在.json文件里修改plants的string即可。相对数组坐标对应其在地图的位置（不能非法）");
        label->resize(600,800);
        label->move(200,-150);
         Page->setText(QString::number(page)+"/"+QString::number(finalpage));
    }
    if(page==8){
        label->setText("地图格数字含义：0:水上不可种格，1：路径，2：出怪口，3：可种格，4：家");
        label->resize(600,800);
        label->move(200,-150);
         Page->setText(QString::number(page)+"/"+QString::number(finalpage));
    }
    if(page==9){
        label->setText("关于词缀：词缀分为敌方词缀和我方词缀，我方词缀部分植物可装部分词缀，这里是我方词缀槽，击杀敌人有概率获得一个随机词缀。敌人吃掉植物也会获得词缀。鼠标右键即可卸掉一个词缀。");
        pix->resize(200,400);
        QPixmap pixmap;
        pix->move(0,200);
        pixmap.load(":/help/Images/a5.png");
        pix->setScaledContents(true);
        pixmap.scaled(pix->size());

        pix->setPixmap(pixmap);
        pix->show();
        Page->setText(QString::number(page)+"/"+QString::number(finalpage));
    }
    if(page==10){
        pix->hide();
        label->resize(600,800);
        label->move(200,-100);
         label->setText("关于我方词缀：狂暴：伤害增加;弱化：群攻;治疗术：固定时间回血;晕眩：减速或定身，只有寒冰射手装备才会定身;斩杀：直接秒杀一个僵尸，但是秒杀后词条会消失（如果同时还有群攻可以秒杀一群僵尸）;治疗术，斩杀，弱化只能用于近战塔，晕眩只能用于远程塔，狂暴都能用。");
        Page->setText(QString::number(page)+"/"+QString::number(finalpage));
    }
    if(page==11){
        pix->hide();
        label->resize(600,800);
        label->move(200,-100);
        label->setText("关于敌方词缀：疾跑：跑得快；净化：免疫减速和定身；干扰：近战塔伤害无效（包括樱桃炸弹）；闪现：瞬间移动三个格的距离（然后词缀会消失）。");
        Page->setText(QString::number(page)+"/"+QString::number(finalpage));
    }
    if(page==12){
        label->resize(600,800);
        label->move(200,-100);
        label->setText("僵尸会从一条或多条路径出发进攻，有普通僵尸，铁桶僵尸，橄榄球僵尸三种，祝你好运！");
        Page->setText(QString::number(page)+"/"+QString::number(finalpage));
    }
}
