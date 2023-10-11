#ifndef QQSTACKEDWIDGET_H
#define QQSTACKEDWIDGET_H

#include <QStackedWidget>

class QQStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit QQStackedWidget(QWidget *parent = nullptr);

private:

    //QList<QWidget *> widgetList;

signals:

};

#endif // QQSTACKEDWIDGET_H
