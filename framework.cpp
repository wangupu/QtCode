#include "framework.h"
#include "ui_framework.h"


FrameWork::FrameWork(QWidget *parent) :
    MouseEvent(parent),
    ui(new Ui::FrameWork)
{
    ui->setupUi(this);

    m_pDataBase = new DatabaseManager(this);
    m_pCenterWidget = new CenterWidget;
    m_pCenterWidget->setDatabaseManager(m_pDataBase);

    m_pRegisterManager = new RegisterManager(this);
    m_pRegisterManager->hide();

    // 初始化ConfigManager
    m_pConfigManager = new ConfigManager(this);
    // 加载保存的窗口几何信息
    QRect savedGeometry = m_pConfigManager->loadWindowGeometry();

    //this->setWindowFlags(Qt::FramelessWindowHint);

    m_pTitleBar = new TitleBar;
    m_pStatusBar = new StatusBar;
    m_pMainWidget = new mainWidget;

    ui->layoutTitleBar->addWidget(m_pTitleBar);
    ui->layoutCenter->addWidget(m_pCenterWidget);//默认界面
    ui->layoutStatusBar->addWidget(m_pStatusBar);

    this->setGeometry(savedGeometry);

    connect(m_pCenterWidget,&CenterWidget::sendMessage, m_pStatusBar, &StatusBar::onRecvMessage);

    //连接登陆成功的信号
    connect(m_pCenterWidget, &CenterWidget::loginSuccess, this, &FrameWork::switchToManiWidget); // 连接登录成功信号

    // 连接注册界面信号
    connect(m_pCenterWidget, &CenterWidget::requestRegister, this, [=]() {
        // 切换到注册界面
        ui->layoutCenter->removeWidget(m_pCenterWidget);
        m_pCenterWidget->hide();
        ui->layoutCenter->addWidget(m_pRegisterManager);
        m_pRegisterManager->show();
    });
    connect(m_pRegisterManager, &RegisterManager::returnToLogin, this, [=]() {
        ui->layoutCenter->removeWidget(m_pRegisterManager);
        m_pRegisterManager->hide();
        ui->layoutCenter->addWidget(m_pCenterWidget);
        m_pCenterWidget->show();
        m_pCenterWidget->showRegisterManager();
    });

    //连接返回主界面的信号
    connect(m_pMainWidget, &mainWidget::returnToMain, this, [=]() {
        // 移除主界面
        ui->layoutCenter->removeWidget(m_pMainWidget);
        m_pMainWidget->hide();
        // 重新显示登录界面
        ui->layoutCenter->addWidget(m_pCenterWidget);
        m_pCenterWidget->show();
    });

    connect(m_pTitleBar,&TitleBar::showWidgetStatus,this,[=](int statusType){
        switch (statusType) {
        case 0:this->close(); break;
        case 1:this->showMaximized();break;
        case 2:this->showMinimized();break;
        case 3:this->showNormal();break;
        default:break;
        }
    });
}

void FrameWork::switchToManiWidget()
{
    // 移除当前中心窗口（登录界面）
    ui->layoutCenter->removeWidget(m_pCenterWidget);
    m_pCenterWidget->hide();
    // 添加主界面
    ui->layoutCenter->addWidget(m_pMainWidget);
    m_pMainWidget->show();
}



FrameWork::~FrameWork()
{
    // 保存窗口几何信息，程序结束时一定会运行析构函数，在这里保存窗口信息比较靠谱
    m_pConfigManager->saveWindowGeometry(this->geometry());
    delete ui;
}
