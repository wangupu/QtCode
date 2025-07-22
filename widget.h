#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "login.h"
#include "mainwidget.h"
#include "centerwidget.h"
#include <QStackedLayout>

namespace Ui {
class widget;
}

class widget : public QWidget
{
    Q_OBJECT

public:
    explicit widget(QWidget *parent = nullptr);
    ~widget();

private:
    Ui::widget *ui;
    Login *m_pLogin;
    mainWidget *m_pMainWidget;
    CenterWidget *m_pCenterWidget;
    QStackedLayout *m_pQStackedLayout;
};

#endif // WIDGET_H
