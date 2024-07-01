#ifndef CHOOSESAVE_H
#define CHOOSESAVE_H
#include <QJsonObject> // { }
#include <QJsonArray> // [ ]
#include <QJsonDocument> // 解析Json
#include <QJsonValue> // int float double bool null { } [ ]
#include <QJsonParseError>
#include <QDialog>
#include<QMessageBox>
#include<QPushButton>
namespace Ui {
class choosesave;
}
//选择存档界面
class choosesave : public QDialog
{
    Q_OBJECT

public:
    explicit choosesave(QWidget *parent = nullptr);
    ~choosesave();

private:
    Ui::choosesave *ui;
    QPushButton *level1;//点击后，存这个关卡
    QPushButton *level2;
    QPushButton*level3;
    QPushButton *level4;
private slots:
    void level1_clicked();
    void level2_clicked();
    void level3_clicked();
    void level4_clicked();
};

#endif // CHOOSESAVE_H
