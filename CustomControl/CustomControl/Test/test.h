#ifndef TEST_H
#define TEST_H

#include <QWidget>

class Test : public QWidget
{
    Q_OBJECT

public:
    Test(QWidget *parent = 0);

    QSize sizeHint()            const;
};

#endif // TEST_H
