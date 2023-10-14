#ifndef QCUSTOMRECOMMENDWIDGET_H
#define QCUSTOMRECOMMENDWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
class QCustomRecommendWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QCustomRecommendWidget(QWidget *parent = nullptr);
    QSize sizeHint() const;

private:
    QStackedWidget *stackedW;
    QPushButton *btnPrevious;
    QPushButton *btnNext;



signals:

};

#endif // QCUSTOMRECOMMENDWIDGET_H
