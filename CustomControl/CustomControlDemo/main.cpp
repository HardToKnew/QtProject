#include "customcontroldemo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomControlDemo w;
    w.show();
    return a.exec();
}
