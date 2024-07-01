#include "maptest.h"
#include "ui_maptest.h"

maptest::maptest(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::maptest)
{
    ui->setupUi(this);
}

maptest::~maptest()
{
    delete ui;
}
