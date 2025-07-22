#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class StatusBar;
}

class StatusBar : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = nullptr);
    ~StatusBar();

public slots:
    void onRecvMessage(const QString &);
    void clearMessage();

private:
    Ui::StatusBar *ui;
    QTimer *m_pTimer;
};

#endif // STATUSBAR_H
