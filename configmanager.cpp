#include "configmanager.h"

ConfigManager::ConfigManager(QWidget *parent) : QWidget(parent)
{
    // 使用相对路径，确保程序可移植性
    m_settings = new QSettings("config.ini", QSettings::IniFormat, this);
}

void ConfigManager::saveWindowGeometry(const QRect &geometry)
{
    m_settings->beginGroup("WindowGeometry");

    m_settings->setValue("x", geometry.x());
    m_settings->setValue("y", geometry.y());
    m_settings->setValue("width", geometry.width());
    m_settings->setValue("height", geometry.height());
    m_settings->setValue("isMaximized", qobject_cast<QWidget*>(parent())->isMaximized());
    m_settings->endGroup();
    m_settings->sync(); // 立即写入文件
}

QRect ConfigManager::loadWindowGeometry()
{
    m_settings->beginGroup("WindowGeometry");
    int x = m_settings->value("x", 100).toInt(); // 默认值100
    int y = m_settings->value("y", 100).toInt(); // 默认值100
    int width = m_settings->value("width", 800).toInt(); // 默认宽度800
    int height = m_settings->value("height", 600).toInt(); // 默认高度600
    bool isMaximized = m_settings->value("isMaximized", false).toBool();

    m_settings->endGroup();
    if(isMaximized){
        qobject_cast<QWidget*>(parent())->showMaximized();
    }

    return QRect(x, y, width, height);
}
