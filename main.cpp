#include "framework.h"
#include "widget.h"
#include <QApplication>
#include "serialport.h"
#include <QSerialPortInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //widget w;
    FrameWork w;
    //SerialPort w;
    w.show();


    QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
    qDebug() << "Total number of availiable ports" << list.count();

    for(auto &serialportinfo : list){
        qDebug() << "Port:" << serialportinfo.portName();
        qDebug() << "Location:" << serialportinfo.systemLocation();
        qDebug() << "Description:" << serialportinfo.description();
        qDebug() << "Manufactutor:" << serialportinfo.manufacturer();
        qDebug() << "Vendor Indentifier:" << serialportinfo.vendorIdentifier();
    }


    return a.exec();
}
