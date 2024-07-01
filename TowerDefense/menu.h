#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include<QPushButton>
#include<QMediaPlayer>
namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();
private slots:
    void returnbutton_clicked();

private:
    Ui::menu *ui;
    QPushButton * returnbutton;
    QMediaPlayer * MenuMediaPlayer;
};

#endif // MENU_H
