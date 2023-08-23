#include "qqmusicdemo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QQMusicDemo w;
    w.show();
    return a.exec();
}
