#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QWidget>
#include <QSettings>
#include <QRect>

class ConfigManager : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigManager(QWidget *parent = nullptr);

    // 保存窗口位置信息
    void saveWindowGeometry(const QRect &geometry);
    // 加载窗口位置信息
    QRect loadWindowGeometry();


private:
    QSettings *m_settings;
};

#endif // CONFIGMANAGER_H
