#include "mouseevent.h"
#include <QDebug>
#include <QMessageBox>

MouseEvent::MouseEvent(QWidget *parent)
    : QWidget(parent)
{
    setTitleBarHidden(true);

}


void MouseEvent::setTitleBarHidden(bool isHidden) {
    if (isHidden) {
        this->setWindowFlags(Qt::FramelessWindowHint);    // 隐藏标题栏
    }
}
// Qt5: event->globalPos(), Qt6: event->globalPosition().toPoint()
// 窗口左上角的居中坐标: frameGeometry().topLeft()
// 计算差值：鼠标的坐标 - 窗口的位置：保证拖动的时候，鼠标位置与窗口相对位置不变
void MouseEvent::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton){
#ifdef Q_OS_WIN     // 在windows系统下
    ReleaseCapture();  // 释放当前鼠标捕获
    // 发送系统命令：SC_MOVE + HTCAPTION 组合模拟标题栏拖动
    SendMessage(HWND(winId()), WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);

#else
         //m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
         m_dragPosition = event->globalPos() - frameGeometry().topLeft();
#endif
        //qDebug() << "mousePressEvent";
    }
}

void MouseEvent::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);//可以用来消除参数未被使用的报错
}


void MouseEvent::mouseReleaseEvent(QMouseEvent *)//不写参数这些类型也可以消除
{
    //qDebug() << "mouseReleaseEvent";
}

//确认是否要关闭窗口的事件
void MouseEvent::closeEvent(QCloseEvent *event)
{
    //qDebug() << "QCloseEvent";
    QMessageBox msgbox;
    msgbox.setText("确定要关闭吗？");
    msgbox.setWindowTitle("警告，警告！");
    msgbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgbox.setDefaultButton(QMessageBox::No);
    switch (msgbox.exec()) {
        case QMessageBox::Yes:
        event->accept();
        break;
    case QMessageBox::No:
        event->ignore();
        break;
    default:
        break;
    }
}

#ifdef Q_OS_WIN
#else
void MouseEvent::mouseMoveEvent(QMouseEvent *event)  {
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - m_dragPosition);
        qDebug() << "mouseMoveEvent";
    }
}

void MouseEvent::mouseReleaseEvent(QMouseEvent *event) {
    qDebug() << "mouseReleaseEvent";
}
#endif
