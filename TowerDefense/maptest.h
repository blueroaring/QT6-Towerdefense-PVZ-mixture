#ifndef MAPTEST_H
#define MAPTEST_H

#include <QMainWindow>

namespace Ui {
class maptest;
}

class maptest : public QMainWindow
{
    Q_OBJECT

public:
    explicit maptest(QWidget *parent = nullptr);
    ~maptest();

private:
    Ui::maptest *ui;
};

#endif // MAPTEST_H
