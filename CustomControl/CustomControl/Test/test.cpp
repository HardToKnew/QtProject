#include "test.h"

Test::Test(QWidget *parent) :
    QWidget(parent)
{
}

QSize Test::sizeHint() const
{
    return QSize(30,30);
}
