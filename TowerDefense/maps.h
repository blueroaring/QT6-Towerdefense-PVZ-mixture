#ifndef MAPS_H
#define MAPS_H

#include <QWidget>
#include<QMediaPlayer>
#include<QPushButton>
#include <QJsonObject> // { }
#include <QJsonArray> // [ ]
#include <QJsonDocument> // 解析Json
#include <QJsonValue> // int float double bool null { } [ ]
#include <QJsonParseError>
namespace Ui {
class maps;
}

class maps : public QWidget
{
    Q_OBJECT

public:
    explicit maps(QWidget *parent = nullptr);
    ~maps();
    void load_from_file();//读档

private slots:
    void returnbutton_clicked();
    void level1_clicked();
    void level2_clicked();
    void level3_clicked();
    void level4_clicked();
    void load_clicked();
private:
    Ui::maps *ui;
    QMediaPlayer * MediaPlayer;
    QPushButton * returnbutton;//返回主界面
    QPushButton * level1;//关卡入口
    QPushButton *level2;
    QPushButton *level3;
    QPushButton *level4;
    QPushButton *load;//读档入口
};

#endif // MAPS_H
