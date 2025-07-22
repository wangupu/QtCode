#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QWidget>
#include <QSerialPort>

namespace Ui {
class SerialPort;
}

class SerialPort : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPort(QWidget *parent = nullptr);
    ~SerialPort();

    void initLization();        //初始化串口参数

public slots:
    void onOpenSerialport();    //打开串口的槽函数
    void onRecvMessage();       //接收信号的槽函数
    void onSendMessage();
    void onClearMessage();

private:
    Ui::SerialPort *ui;
    bool m_isOpend;         //判断串口是否打开的标志
    QSerialPort *m_pSerialport;
};

#endif // SERIALPORT_H
