#include "qcustommusiclable.h"

QCustomMusicLable::QCustomMusicLable(QWidget *parent)
    : QWidget{parent}
{

}

QSize QCustomMusicLable::sizeHint() const
{
    return QSize(164,164);
}
