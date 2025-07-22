#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

namespace Ui {
class mainWidget;
}

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

signals:
    void display(int);
    void returnToMain();

public slots:
    void onShowSys();
    void onShowCount();
    void onShowOutlook();
    void onShowAssist();

private:
    Ui::mainWidget *ui;
};

#endif // MAINWIDGET_H
