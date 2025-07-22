#include "serialport.h"
#include "ui_serialport.h"
#include <QSerialPortInfo>
#include <qdebug.h>
#include <QMessageBox>

SerialPort::SerialPort(QWidget *parent) :
    QWidget(parent),
    m_isOpend(false),
    ui(new Ui::SerialPort)
{
    ui->setupUi(this);
    initLization();
    m_pSerialport = new QSerialPort(this);
    connect(ui->btnOpen,&QPushButton::clicked,this,&SerialPort::onOpenSerialport);
    connect(ui->btnSend, &QPushButton::clicked, this, &SerialPort::onSendMessage);
    connect(ui->btnClear, &QPushButton::clicked, this, &SerialPort::onClearMessage);

}


void SerialPort::initLization()
{
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    for(auto &port : portList){
        ui->comboBoxPort->addItem(port.portName());
    }

    //初始化波特率
    QList<QPair<QString,QSerialPort::BaudRate>> baudRates{
        {"1200",QSerialPort::Baud1200},
        {"2400",QSerialPort::Baud2400},
        {"4800",QSerialPort::Baud4800},
        {"9600",QSerialPort::Baud9600},
        {"19200",QSerialPort::Baud19200},
        {"38400",QSerialPort::Baud38400},
        {"57600",QSerialPort::Baud57600},
        {"115200",QSerialPort::Baud115200}
    };

    for(const auto &baudRate : baudRates){
        ui->comboBoxBaudRate->addItem(baudRate.first,baudRate.second);
    }

    //初始化数据位
    QList<QPair<QString,QSerialPort::DataBits>> dataBits {
        {"8",QSerialPort::DataBits::Data8},
        {"7",QSerialPort::DataBits::Data7},
        {"6",QSerialPort::DataBits::Data6},
        {"5",QSerialPort::DataBits::Data5}
    };

    for(const auto &dataBit : dataBits){
        ui->comboBoxDataBits->addItem(dataBit.first,dataBit.second);
    }

    //初始化停止位
    QList<QPair<QString,QSerialPort::StopBits>> stopBits {
        {"1",QSerialPort::StopBits::OneStop},
        {"1.5",QSerialPort::StopBits::OneAndHalfStop},
        {"2",QSerialPort::StopBits::TwoStop}
    };

    for(const auto &stopBits : stopBits){
        ui->comboBoxStopBits->addItem(stopBits.first,stopBits.second);
    }

    //初始化校验位
    QList<QPair<QString,QSerialPort::Parity>> parityBits {
        {"NONE",QSerialPort::Parity::NoParity},
        {"ODD",QSerialPort::Parity::OddParity},
        {"EVEN",QSerialPort::Parity::EvenParity},
        {"MARK",QSerialPort::Parity::MarkParity},
        {"SPACE",QSerialPort::Parity::SpaceParity}
    };

    for(const auto &parityBit : parityBits){
        ui->comboBoxParityBits->addItem(parityBit.first,parityBit.second);
    }
}

void SerialPort::onOpenSerialport()
{
    if(m_isOpend){
        //qDebug() << "Serialport is opend!";
        //如果是打开状态就设置为关闭
        m_pSerialport->close();
        ui->btnOpen->setText("打开");
        //设置使能，当打开时其他的状态不可选取
        ui->comboBoxPort->setEnabled(true);
        ui->comboBoxBaudRate->setEnabled(true);
        ui->comboBoxDataBits->setEnabled(true);
        ui->comboBoxStopBits->setEnabled(true);
        ui->comboBoxParityBits->setEnabled(true);
        ui->comboBoxFlowControl->setEnabled(true);

        m_isOpend = false;
        qDebug() << "串口已关闭";
        return;
    }

    //设置串口参数
    m_pSerialport->setPortName(ui->comboBoxPort->currentText());
    m_pSerialport->setBaudRate(ui->comboBoxBaudRate->currentData().toUInt());
    m_pSerialport->setDataBits(static_cast<QSerialPort::DataBits>(ui->comboBoxDataBits->currentData().toInt()));
    m_pSerialport->setStopBits(static_cast<QSerialPort::StopBits>(ui->comboBoxStopBits->currentData().toInt()));
    m_pSerialport->setParity(static_cast<QSerialPort::Parity>(ui->comboBoxParityBits->currentData().toInt()));

    if(!m_pSerialport->open(QIODevice::ReadWrite)){
        qDebug() << "串口打开失败";
        return ;
    }

    //如果是关闭的状态，就把状态设置为打开
    m_isOpend = true;
    ui->comboBoxPort->setEnabled(false);
    ui->comboBoxBaudRate->setEnabled(false);
    ui->comboBoxDataBits->setEnabled(false);
    ui->comboBoxStopBits->setEnabled(false);
    ui->comboBoxParityBits->setEnabled(false);
    ui->comboBoxFlowControl->setEnabled(false);
    ui->btnOpen->setText("关闭");

    //串口信号和槽函数的关联
    connect(m_pSerialport,&QIODevice::readyRead,this,&SerialPort::onRecvMessage);

    qDebug() << "串口打开成功";
}

//接收数据
void SerialPort::onRecvMessage()
{
    QByteArray buff;
    qDebug() << "Receive data";
    //取出来新的数据
    buff = m_pSerialport->readAll();
    //把取出来的数据放到textEdit里
    if(buff.isEmpty()){
        return ;
    }
    ui->textEditReceive->append("接收到的数据：\n" + buff);
}

//发送数据
void SerialPort::onSendMessage()
{

    if (!m_isOpend || !m_pSerialport->isOpen()) {
        qDebug() << "串口未打开，无法发送";

        return;
    }

    QString text = ui->textEditSend->toPlainText();
    if (text.isEmpty()) {
        qDebug() << "发送内容为空";
        return;
    }

    QByteArray sendData = text.toUtf8();
    m_pSerialport->write(sendData);
    ui->textEditReceive->append("发送的数据：\n" +sendData);

    qDebug() << "发送数据成功！" ;
}

void SerialPort::onClearMessage()
{
    ui->textEditReceive->clear();
    qDebug() << "Clear data";
}



SerialPort::~SerialPort()
{
    delete ui;
}
