QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
win32 {
contains(QT_ARCH, i386) {
#指定编译生成的可执行文件到bin目录
        DESTDIR += $$PWD/bin/x32
        CONFIG(debug,debug|release){
            TARGET = QQMusicDemo_debug_x86
        }
        CONFIG(release,debug|release){
            TARGET= QQMusicDemo_release_x86
        }
    } else {
        #指定编译生成的可执行文件到bin目录
        DESTDIR += $$PWD/bin/x64

        CONFIG(debug,debug|release){
            TARGET= QQMusicDemo_debug_x64
        }
        CONFIG(release,debug|release){
            TARGET= QQMusicDemo_release_x64
        }
    }
#程序版本
    VERSION = 0.0.0.1
#程序图标
    #RC_ICONS = app.ico
#公司名称
    QMAKE_TARGET_COMPANY ="HardToKnew"
#程序说明
    QMAKE_TARGET_DESCRIPTION = "QQMusicDemo"
#版权信息
    QMAKE_TARGET_COPYRIGHT = "Copyright(C) 2023 HardToKnew. All rights reserved."
#程序名称
    QMAKE_TARGET_PRODUCT = "QQMusicDemo"
#程序语言
#0x0800代表和系统当前语言一致
    RC_LANG = 0x0800
}
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    qqmusicdemo.cpp \
    src/qqmusiccenterw.cpp \
    src/qqmusiclistw.cpp \
    src/qqmusicmenu.cpp \
    src/qqmusicplay.cpp

HEADERS += \
    qqmusicdemo.h \
    src/qqmusiccenterw.h \
    src/qqmusiclistw.h \
    src/qqmusicmenu.h \
    src/qqmusicplay.h

FORMS += \
    qqmusicdemo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

RC_ICONS = $$PWD/images/QQMusic.ico


