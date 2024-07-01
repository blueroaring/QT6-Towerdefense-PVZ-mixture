#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSoundEffect>
#include<QMediaPlayer>
#include<QPushButton>
#include<QPaintEvent>
#include"choosesave.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class AudioPlayer;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newstartgame_clicked();
    void choosegame_clicked();
    void menu_clicked();
    void play_rules_clicked();
    void exit_game_clicked();
      void level5_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer * MainWindowplayer;
    QPushButton * startButton;// 游戏开始按钮
    QPushButton * optionButton;// 选择项按钮
    QPushButton * menuButton;//图鉴按钮
    QPushButton * helpButton;// 帮助按钮
    QPushButton * exitButton;// 游戏退出按钮
    QPushButton *level5Button;//存地图按钮
    choosesave *a;//存档地图按钮
};
#endif // MAINWINDOW_H
