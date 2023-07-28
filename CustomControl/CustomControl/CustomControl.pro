CONFIG      += plugin debug_and_release
CONFIG(debug, debug|release){
   TARGET = customcontrold
}
else{
   TARGET = customcontrol
}

#或者直接这样，这个$$qtLibraryTarget会在debug下直接加d的
TARGET = $$qtLibraryTarget($$TARGET)

#TARGET      = $$qtLibraryTarget(customcontrol)
TEMPLATE    = lib

HEADERS     = cardashboardplugin.h testplugin.h customcontrol.h
SOURCES     = cardashboardplugin.cpp testplugin.cpp customcontrol.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(Test/test.pri)
include(CarDashBoard/cardashboard.pri)
