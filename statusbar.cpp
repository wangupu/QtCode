#include "statusbar.h"
#include "ui_statusbar.h"

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBar)
{
    ui->setupUi(this);
    m_pTimer = new QTimer(this);
    connect(m_pTimer,&QTimer::timeout,this,&StatusBar::clearMessage);
}

void StatusBar::onRecvMessage(const QString &msg)
{
    ui->labelStatus->setText(msg);
    m_pTimer->start(3000);
}

void StatusBar::clearMessage()
{
    ui->labelStatus->clear();
    m_pTimer->stop();
}

StatusBar::~StatusBar()
{
    delete ui;
}


