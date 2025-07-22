#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H


#include <QWidget>
#include <QMouseEvent>
#include <QCloseEvent>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

class MouseEvent : public QWidget
{
public:
    MouseEvent(QWidget *parent = nullptr);
    void setTitleBarHidden(bool);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
#ifdef Q_OS_WIN
    QPoint m_dragPosition;
#endif

};

#endif // MOUSEEVENT_H
