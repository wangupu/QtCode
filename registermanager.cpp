#include "registermanager.h"
#include "ui_registermanager.h"

RegisterManager::RegisterManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterManager)
{
    ui->setupUi(this);
    connect(ui->btnSure, &QPushButton::clicked, this, [=]() {
        emit returnToLogin();
    });

}

RegisterManager::~RegisterManager()
{
    delete ui;
}
