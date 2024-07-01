#ifndef HELP_H
#define HELP_H

#include <QMainWindow>
#include<QPushButton>
#include<QMediaPlayer>
#include<QWidget>
#include<mainwindow.h>
#include<QLabel>
namespace Ui {
class help;
}

class help : public QWidget
{
    Q_OBJECT

public:
    explicit help(QWidget *parent=nullptr);
    ~help();
    int page;
private slots:
     void returnbutton_clicked();
    void nextpage_clicked();
private:
    Ui::help *ui;
    QMediaPlayer * helpMediaPlayer;
    QPushButton * returnbutton;
    QPushButton * nextbutton;
    QLabel *label;//文字显示
    QLabel *pix;//图片显示
    int finalpage;//总共页数
    QLabel *Page;
};

#endif // HELP_H
