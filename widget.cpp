#include "widget.h"
#include "ui_widget.h"

widget::widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);
    m_pLogin = new Login;
    m_pMainWidget = new mainWidget;
    m_pQStackedLayout = new QStackedLayout(this);

    m_pQStackedLayout->addWidget(m_pLogin);
    m_pQStackedLayout->addWidget(m_pMainWidget);

    connect(m_pLogin,&Login::display,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);
    connect(m_pMainWidget,&mainWidget::display,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);


//    m_pQStackedLayout = new QStackedLayout(this);
//    this->setLayout(m_pQStackedLayout);  // 设置为主布局

//    // 创建登录页面
//    m_pCenterWidget = new CenterWidget();
//    m_pQStackedLayout->addWidget(m_pCenterWidget);

//    // 创建主界面
//    m_pMainWidget = new mainWidget();
//    m_pQStackedLayout->addWidget(m_pMainWidget);

//    // 初始显示登录页面
//    m_pQStackedLayout->setCurrentIndex(0);

//    // 连接登录成功信号
//    connect(m_pCenterWidget, &CenterWidget::loginSuccess, this, [=](){
//        m_pQStackedLayout->setCurrentIndex(1);  // 切换到主界面
//    });

//    // 连接返回信号
//    connect(m_pMainWidget, &mainWidget::returnToMain, this, [=](){
//        m_pQStackedLayout->setCurrentIndex(0);  // 切换回登录界面
//    });
}

widget::~widget()
{
    delete ui;
}
