#include "framework.h"
#include "ui_framework.h"
//测试

FrameWork::FrameWork(QWidget *parent) :
    MouseEvent(parent),
    ui(new Ui::FrameWork)
{
    ui->setupUi(this);

    //this->setWindowFlags(Qt::FramelessWindowHint);

    m_pTitleBar = new TitleBar;
    m_pCenterWidget = new CenterWidget;
    m_pStatusBar = new StatusBar;

    ui->layoutTitleBar->addWidget(m_pTitleBar);
    ui->layoutCenter->addWidget(m_pCenterWidget);
    ui->layoutStatusBar->addWidget(m_pStatusBar);

    connect(m_pCenterWidget,&CenterWidget::sendMessage, m_pStatusBar, &StatusBar::onRecvMessage);

    connect(m_pTitleBar,&TitleBar::showWidgetStatus,this,[=](int statusType){
        switch (statusType) {
        case 0:
            this->close();
            break;
        case 1:
            this->showMaximized();
            break;
        case 2:
            this->showMinimized();
            break;
        case 3:
            this->showNormal();
            break;
        default:
        break;
        }
    });

}

FrameWork::~FrameWork()
{
    delete ui;
}
