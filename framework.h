#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <QWidget>
#include <titlebar.h>
#include <centerwidget.h>
#include <statusbar.h>
#include <QLayout>
#include <QPoint>
#include <mainwidget.h>
#include "mouseevent.h"
#include "databasemanager.h"
#include "configmanager.h"
#include "registermanager.h"


namespace Ui {
class FrameWork;
}

class FrameWork : public MouseEvent
{
    Q_OBJECT

public:
    explicit FrameWork(QWidget *parent = nullptr);
    ~FrameWork();

public slots:
    void switchToManiWidget();

private:
    Ui::FrameWork *ui;

    TitleBar *m_pTitleBar;
    CenterWidget *m_pCenterWidget;
    StatusBar *m_pStatusBar;
    DatabaseManager *m_pDataBase;
    ConfigManager *m_pConfigManager;
    mainWidget *m_pMainWidget;
    RegisterManager *m_pRegisterManager;

};

#endif // FRAMEWORK_H
