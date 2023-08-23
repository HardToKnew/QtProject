#include "qqmusicmenu.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QFontDatabase>
#include <QAction>
#include <QDebug>
QQMusicMenu::QQMusicMenu(QWidget *parent)
    : QWidget{parent}
{
    initMusicMenu();
    this->setMouseTracking(true);
}

QSize QQMusicMenu::sizeHint() const
{
    return QSize(1020,80);
}

void QQMusicMenu::setSearchEdit()
{
    //qDebug()<<"setSearchEdit";
    if(leSearch->text().isEmpty())//搜索框无输入
    {
        btnSearch->setVisible(false);
        acSearchIcon->setVisible(true);
        QFont  SearchFont;
        SearchFont.setPointSize(10);
        leSearch->setFont(SearchFont);
        leSearch->setReadOnly(true);
        this->clearFocus();
        //leSearch->setTextMargins(16,1,1,1);//设置光标位置
        leSearch->setPlaceholderText("搜索音乐");//占位符
    }
}

bool QQMusicMenu::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == leSearch)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);
            if(mouseEvent!=NULL)
            {
                if( mouseEvent->button() == Qt::LeftButton)//鼠标左键按下
                {

                    btnSearch->setVisible(true);
                    acSearchIcon->setVisible(false);
                    QFont  SearchFont;
                    SearchFont.setPointSize(15);
                    leSearch->setFont(SearchFont);
                    leSearch->setReadOnly(false);
                    leSearch->setTextMargins(12,1,1,1);//设置光标位置
                    leSearch->setPlaceholderText("");//占位符
                }
            }
            return QObject::eventFilter(obj,event);
        }
        return false;
    }

    /*if(obj == this)
    {
        qDebug()<<event->type();
        if (event->type() == QEvent::MouseButtonPress)
        {
            qDebug()<<"MouseButtonPress";
            QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);
            if(mouseEvent!=NULL)
            {
                if( mouseEvent->button() == Qt::LeftButton)//鼠标左键按下
                {
                    setSearchEdit();
                }
            }
            return QObject::eventFilter(obj,event);
        }
        return false;
    }*/
    return QObject::eventFilter(obj,event);
}

void QQMusicMenu::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton)//鼠标左键按下
    {
        setSearchEdit();
    }
}



void QQMusicMenu::initMusicMenu()
{

    //标题栏-----------
    QPixmap pix(":/images/QQMusic.png");
    pix = pix.scaled(24,24,Qt::KeepAspectRatio);
    lbIcon = new QLabel;//图标
    lbIcon->setPixmap(pix);
    lbIcon->setFixedSize(25,25);
    lbTitle = new QLabel;
    lbTitle->setText("QQ音乐");//文字
    lbTitle->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);


    //经过裁切过的字体库
    int fontId = QFontDatabase::addApplicationFont(QStringLiteral(":/font/SweiHalfMoonCJKsc-Bold.subset.ttf"));
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font;
    if (fontFamilies.size() > 0)
    {
        font.setFamily(fontFamilies[0]);//设置全局字体
    }
    font.setPointSize(13);
    lbTitle->setFont(font);//设置标题栏 QQ音乐字体


    //图标和标题栏布局
    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->setContentsMargins(25, 0, 0, 10);
    titleLayout->addSpacing(40);
    titleLayout->addWidget(lbIcon);
    titleLayout->addSpacing(0);
    titleLayout->addWidget(lbTitle);
    //标题栏图标及标题栏面板
    QWidget *wTitle = new QWidget;
    wTitle->setFixedSize(200,50);
    wTitle->setLayout(titleLayout);
    //----------------

    //控制按钮面板-----------
    QWidget *wBtn = new QWidget;
    QPalette pal(wBtn->palette());

    //设置背景白色
    pal.setColor(QPalette::Background, Qt::white);
    wBtn->setAutoFillBackground(true);
    wBtn->setPalette(pal);
    //控制面板栏布局
    QHBoxLayout *btnLayout = new QHBoxLayout;
    titleLayout->setContentsMargins(0, 0, 0, 0);
    wBtn->setLayout(btnLayout);
    
    QSize btnSize(28,22);//部分按钮大小
    //后退按钮
    btnBack = new QPushButton;
    btnBack->setFixedSize(btnSize);
    btnBack->setStyleSheet("QPushButton{border-image: url(:/images/back-96-black.png);}"
                           "QPushButton:hover{border-image: url(:/images/back-96-green.png);}"
                           "QPushButton{border-width: 4px  7px}");
    btnBack->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    //前进按钮
    btnForward = new QPushButton;
    btnForward->setFixedSize(btnSize);
    btnForward->setStyleSheet("QPushButton{border-image: url(:/images/forward-96-black.png);}"
                           "QPushButton:hover{border-image: url(:/images/forward-96-green.png);}"
                           "QPushButton{border-width: 4px  7px}");
    btnForward->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    //刷新按钮
    btnRenew = new QPushButton;
    btnRenew->setFixedSize(btnSize);
    btnRenew->setStyleSheet("QPushButton{border-image: url(:/images/renew-16-black.png);}"
                            "QPushButton:hover{border-image: url(:/images/renew-16-green.png);}"
                            "QPushButton{margin: 3px 6px 3px 6px}");
    btnRenew->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    //搜索框--------
    leSearch = new QLineEdit;
    acSearchIcon = new QAction;
    QPixmap SearchIcon(":/images/search-16-black.png");
    acSearchIcon->setIcon(SearchIcon);
    btnSearch = new QPushButton;
    btnSearch->setCursor(Qt::ArrowCursor);//设置鼠标指针样式
    btnSearch->setFixedSize(16,16);
    btnSearch->setStyleSheet("QPushButton{border-image: url(:/images/search-16-black.png);}"
                             "QPushButton:hover{border-image: url(:/images/search-16-green.png);}"
                             "QPushButton{margin: 0px 0px 0px 0px}");

    QFont  SearchFont;
    SearchFont.setPointSize(10);
    leSearch->setFont(SearchFont);
    leSearch->setTextMargins(16,1,1,1);//设置光标位置

    leSearch->setFixedHeight(33);
    leSearch->setMinimumWidth(160);
    leSearch->setPlaceholderText("搜索音乐");//占位符
    leSearch->setStyleSheet("QLineEdit{border-radius: 16px;"
                            "background-color: rgb(227, 227, 227);"
                            "}");
    leSearch->installEventFilter(this);//安装事件过滤器

    leSearch->addAction(acSearchIcon,QLineEdit::LeadingPosition);
    QHBoxLayout *leSearchLayout = new QHBoxLayout;
    leSearch->setLayout(leSearchLayout);
    leSearchLayout->addStretch();
    leSearchLayout->addWidget(btnSearch,Qt::AlignRight);
    leSearchLayout->addSpacing(4);
    btnSearch->setVisible(false);
    //听歌识曲------------
    btnListen = new QPushButton;
    btnListen->setFixedSize(btnSize);
    btnListen->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnListen->setStyleSheet("QPushButton{border-image: url(:/images/listen-16-black.png);}"
                             "QPushButton:hover{border-image: url(:/images/listen-16-green.png);}"
                             "QPushButton{margin: 3px 6px 3px 6px}");

    //-----登录按钮------暂时只写未登录状态
    btnLogin = new QPushButton;//90 x 24
    lbLoginIcon = new QLabel;
    lbLoginText = new QLabel;
    btnLogin->setFixedSize(90,24);
    btnLogin ->setStyleSheet("QPushButton{background-color: rgb(255,255,255);"
                            "border: none;}");
    lbLoginIcon->setFixedSize(24,24);
    lbLoginIcon->setStyleSheet("QLabel{border-radius: 12px;border-image: url(:/images/login-96.png)}");
    lbLoginIcon->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    lbLoginText->setText("点击登录");
    lbLoginText->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    lbLoginText->setStyleSheet("QLabel{color: rgb(124,124,124);"
                               "}");
    QHBoxLayout *loginLayout = new QHBoxLayout;
    loginLayout->setContentsMargins(0,0,5,0);
    btnLogin->setLayout(loginLayout);
    loginLayout->addWidget(lbLoginIcon);
    loginLayout->addSpacing(5);
    loginLayout->addWidget(lbLoginText);
    //换肤按钮
    btnSkin = new QPushButton;
    btnSkin->setFixedSize(btnSize);
    btnSkin->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnSkin->setStyleSheet("QPushButton{border-image: url(:/images/skin-32-black.png);}"
                           "QPushButton:hover{border-image: url(:/images/skin-32-green.png);}"
                           "QPushButton{margin: 1px 4px 1px 4px}");
    //主菜单
    btnMenu = new QPushButton;
    btnMenu->setFixedSize(btnSize);
    btnMenu->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnMenu->setStyleSheet("QPushButton{border-image: url(:/images/mainMenu-32-black.png);}"
                           "QPushButton:hover{border-image: url(:/images/mainMenu-32-green.png);}"
                           "QPushButton{margin: 1px 4px 1px 4px}");

    //竖线
    line = new QFrame;
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Plain);
    line->setLineWidth(1);
    line->setFixedHeight(20);
    line->setContentsMargins(0,0,0,0);
    QPalette palette = line->palette();
    palette.setColor(QPalette::WindowText, QColor(124,124,124));
    line->setPalette(palette);

    //精简模式
    btnSimple = new QPushButton;
    btnSimple->setFixedSize(btnSize);
    btnSimple->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnSimple->setStyleSheet("QPushButton{border-image: url(:/images/segmdl2-multitask-96-black.png);}"
                             "QPushButton:hover{border-image: url(:/images/segmdl2-multitask-96-green.png);}"
                             "QPushButton{margin: 1px 4px 1px 4px}");


    //最小化按钮
    btnMinimize = new QPushButton;
    btnMinimize->setFixedSize(btnSize);
    btnMinimize->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnMinimize->setStyleSheet("QPushButton{border-image: url(:/images/minimize-96-black.png);}"
                               "QPushButton:hover{border-image: url(:/images/minimize-96-green.png);}"
                               "QPushButton{margin: 3px 6px 3px 6px}");
    connect(btnMinimize, &QAbstractButton::clicked, this, [=](){emit btnMinimizeClicked();});
    //最大化按钮
    bMaximized = false;//初始化未被最大化
    btnMaximize = new QPushButton;
    btnMaximize->setFixedSize(btnSize);
    btnMaximize->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnMaximize->setStyleSheet("QPushButton{border-image: url(:/images/maximize-96-black.png);}"
                               "QPushButton:hover{border-image: url(:/images/maximize-96-green.png);}"
                               "QPushButton{margin: 3px 6px 3px 6px}");
    connect(btnMaximize, &QAbstractButton::clicked, this, [=](){
        bMaximized = !bMaximized;
        emit btnMaximizeClicked(bMaximized);
        if(bMaximized)
        {
            btnMaximize->setStyleSheet("QPushButton{border-image: url(:/images/maximize-96-black1.png);}"
                                       "QPushButton:hover{border-image: url(:/images/maximize-96-green1.png);}"
                                       "QPushButton{margin: 3px 6px 3px 6px}");
        } else{
            btnMaximize->setStyleSheet("QPushButton{border-image: url(:/images/maximize-96-black.png);}"
                                       "QPushButton:hover{border-image: url(:/images/maximize-96-green.png);}"
                                       "QPushButton{margin: 3px 6px 3px 6px}");
        }
    });

    //关闭按钮
    btnClose = new QPushButton;
    btnClose->setFixedSize(btnSize);
    btnClose->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnClose->setStyleSheet("QPushButton{border-image: url(:/images/close-96-black.png);}"
                            "QPushButton:hover{border-image: url(:/images/close-96-green.png);}"
                            "QPushButton{margin: 3px 6px 3px 6px}");
    connect(btnClose, &QAbstractButton::clicked, this, [=](){emit btnCloseClicked();});




    //控制面板栏添加控件
    btnLayout->addSpacing(25);
    btnLayout->addWidget(btnBack);
    btnLayout->addWidget(btnForward);
    btnLayout->addWidget(btnRenew);
    btnLayout->addWidget(leSearch);
    btnLayout->addWidget(btnListen);
    btnLayout->addStretch(150);
    btnLayout->addWidget(btnLogin);
    btnLayout->addWidget(btnSkin);
    btnLayout->addWidget(btnMenu);
    btnLayout->addSpacing(3);
    btnLayout->addWidget(line);
    btnLayout->addSpacing(3);
    btnLayout->addWidget(btnSimple);
    btnLayout->addWidget(btnMinimize);
    btnLayout->addWidget(btnMaximize);
    btnLayout->addWidget(btnClose);
    btnLayout->addSpacing(10);
    //btnLayout->addStretch();



    //标题栏布局
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(wTitle);
    mainLayout->addWidget(wBtn);
    mainLayout->setContentsMargins(0,0,0,0);
    this->setLayout(mainLayout);
    //lbIcon->setScaledContents(true);
    //this->installEventFilter(this);

}
