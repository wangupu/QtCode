#include "titlebar.h"
#include "ui_titlebar.h"
#include <QFile>
#include <QDebug>

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TitleBar) {
    ui->setupUi(this);
    loadStyleSheet("D:/QtCode/Frame/css/img.css");
    connect(ui->btnMinisized, &QPushButton::clicked, this, &TitleBar::onMiniSized);
    connect(ui->btnMaxsized, &QPushButton::clicked, this, &TitleBar::onMaxSized);
    connect(ui->btnClose, &QPushButton::clicked, this, &TitleBar::onClose);
}

void TitleBar::onMiniSized() {
    emit showWidgetStatus(MINISIZED);
}

void TitleBar::onMaxSized() {
    if(m_isMaxSized){
        emit showWidgetStatus(RETURN);
        m_isMaxSized = false;
    }else{
        emit showWidgetStatus(MAXSIZED);
        m_isMaxSized = true;
    }
}

void TitleBar::onClose() {
    this->parentWidget()->close();
}

void TitleBar::loadStyleSheet(const QString &path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "css file open failed!";
        return ;
    }
    //QString strFile = file.readAll();
    this->setStyleSheet(file.readAll());
}

TitleBar::~TitleBar() {
    delete ui;
}
