#ifndef CUSTOMCONTROLDEMO_H
#define CUSTOMCONTROLDEMO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CustomControlDemo; }
QT_END_NAMESPACE

class CustomControlDemo : public QMainWindow
{
    Q_OBJECT

public:
    CustomControlDemo(QWidget *parent = nullptr);
    ~CustomControlDemo();

private slots:
    void on_chkCarDashBoard_toggled(bool checked);

    void on_sliderCarDashBoard_valueChanged(int value);

private:
    Ui::CustomControlDemo *ui;
};
#endif // CUSTOMCONTROLDEMO_H
