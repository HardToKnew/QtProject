#include "Test/test.h"
#include "testplugin.h"

#include <QtPlugin>

TestPlugin::TestPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void TestPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TestPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TestPlugin::createWidget(QWidget *parent)
{
    return new Test(parent);
}

QString TestPlugin::name() const
{
    return QLatin1String("Test");
}

QString TestPlugin::group() const
{
    return QLatin1String("CustomControl Widget");
}

QIcon TestPlugin::icon() const
{
    return QIcon();
}

QString TestPlugin::toolTip() const
{
    return QString::fromUtf8("测试");
}

QString TestPlugin::whatsThis() const
{
    return QString::fromUtf8("CustomControl Widget测试");
}

bool TestPlugin::isContainer() const
{
    return false;
}

QString TestPlugin::domXml() const
{
    return QLatin1String("<widget class=\"Test\" name=\"test\">\n</widget>\n");
}

QString TestPlugin::includeFile() const
{
    return QLatin1String("test.h");
}

