#include "CarDashBoard/cardashboard.h"
#include "cardashboardplugin.h"

#include <QtPlugin>

CarDashBoardPlugin::CarDashBoardPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void CarDashBoardPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CarDashBoardPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CarDashBoardPlugin::createWidget(QWidget *parent)
{
    return new CarDashBoard(parent);
}

QString CarDashBoardPlugin::name() const
{
    return QLatin1String("CarDashBoard");
}

QString CarDashBoardPlugin::group() const
{
    return QLatin1String("CustomControl Widget");
}

QIcon CarDashBoardPlugin::icon() const
{
    return QIcon(":/images/CarDashBoard.png");
}

QString CarDashBoardPlugin::toolTip() const
{
    return QString::fromUtf8("汽车仪表盘");
}

QString CarDashBoardPlugin::whatsThis() const
{
    return QString::fromUtf8("自定义汽车仪表盘");
}

bool CarDashBoardPlugin::isContainer() const
{
    return false;
}

QString CarDashBoardPlugin::domXml() const
{
    return QLatin1String("<widget class=\"CarDashBoard\" name=\"carDashBoard\">\n</widget>\n");
}

QString CarDashBoardPlugin::includeFile() const
{
    return QLatin1String("cardashboard.h");
}

