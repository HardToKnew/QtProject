#include "customcontroldemo.h"
#include "ui_customcontroldemo.h"

CustomControlDemo::CustomControlDemo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CustomControlDemo)
{
    ui->setupUi(this);


    connect(ui->wCarDashBoard, &CarDashBoard::RangChanged, ui->sliderCarDashBoard, &QSlider::setRange);
    //ui->wCarDashBoard->setRangle(0,300);
}

CustomControlDemo::~CustomControlDemo()
{
    delete ui;
}


void CustomControlDemo::on_chkCarDashBoard_toggled(bool checked)
{
    ui->wCarDashBoard->setAnimation(checked);
}


void CustomControlDemo::on_sliderCarDashBoard_valueChanged(int value)
{
    ui->wCarDashBoard->setValue(value);
}

