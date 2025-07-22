#include "mainwidget.h"
#include "ui_mainwidget.h"

mainWidget::mainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);

    connect(ui->btnSys,&QPushButton::clicked,this,&mainWidget::onShowSys);
    connect(ui->btnCount,&QPushButton::clicked,this,&mainWidget::onShowCount);
    connect(ui->btnOutlook,&QPushButton::clicked,this,&mainWidget::onShowOutlook);
    connect(ui->btnAssist,&QPushButton::clicked,this,&mainWidget::onShowAssist);
    //用lambda
    connect(ui->btnAbout,&QPushButton::clicked,this,[this](){
        ui->stackedWidget->setCurrentIndex(4);
    });

    connect(ui->btnReturn,&QPushButton::clicked,this,[=](){
        emit returnToMain();
    });

}

void mainWidget::onShowSys()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void mainWidget::onShowCount(){
    ui->stackedWidget->setCurrentIndex(1);
}
void mainWidget::onShowOutlook(){
    ui->stackedWidget->setCurrentIndex(2);
}
void mainWidget::onShowAssist(){
    ui->stackedWidget->setCurrentIndex(3);
}

mainWidget::~mainWidget()
{
    delete ui;
}
