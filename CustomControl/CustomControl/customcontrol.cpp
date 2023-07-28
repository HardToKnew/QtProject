#include "cardashboardplugin.h"
#include "testplugin.h"
#include "customcontrol.h"

CustomControl::CustomControl(QObject *parent)
    : QObject(parent)
{
    m_widgets.append(new CarDashBoardPlugin(this));
    m_widgets.append(new TestPlugin(this));

}

QList<QDesignerCustomWidgetInterface*> CustomControl::customWidgets() const
{
    return m_widgets;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(customcontrol, CustomControl)
#endif // QT_VERSION < 0x050000
