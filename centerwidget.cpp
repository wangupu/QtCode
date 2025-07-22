#include "centerwidget.h"
#include "ui_centerwidget.h"
#include <QFile>
#include <QDebug>

CenterWidget::CenterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CenterWidget)
{
    ui->setupUi(this);

    m_Settings = new QSettings("D:/QtCode/Frame/config.ini",QSettings::IniFormat,this);

    loadStyleSheet("D:/QtCode/Frame/css/img.css");

    m_pTimer = new QTimer(this);
    connect(ui->btnLogin,&QPushButton::clicked,this,&CenterWidget::onLogin);
    connect(ui->btnRegister,&QPushButton::clicked,this,&CenterWidget::onRegister);
    connect(m_pTimer,&QTimer::timeout,this,[=](){
        ui->label->clear();
    });
//    m_userName = readIniSettings().toString();
//    qDebug() << m_userName;
//    m_passWord = readIniSettings().toString();
//    qDebug() << m_passWord;

//    writeIniSettings();
//    m_userName = readIniSettings().toString();
//    qDebug() << "new name" << m_userName ;

}

void CenterWidget::onLogin()
{
    m_pTimer->start(3000);
    QString username = ui->lineUserName->text();
    QString password = ui->linePasswd->text();

    if (!m_dbManager) {
        emit sendMessage("数据库连接错误");
        return;
    }

    // 检查用户名是否存在
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = ?");
    query.addBindValue(username);

    if (!query.exec()) {
        emit sendMessage("查询失败");
        return;
    }

    if (query.next()) {
        // 用户名存在，检查密码
        QString correctPassword = query.value(0).toString();
        if (correctPassword == password) {
            emit sendMessage("登陆成功");
            emit loginSuccess();
        } else {
            emit sendMessage("密码错误");
            ui->linePasswd->clear();
        }
    } else {
        // 用户名不存在
        emit sendMessage("用户名错误");
        ui->lineUserName->clear();
        ui->linePasswd->clear();
    }

//    if(m_dbManager && m_dbManager->checkLogin(username, password)) {
//        emit sendMessage("登陆成功");
//        emit loginSuccess();
//    } else {
//        emit sendMessage("用户名或密码错误");
//        ui->linePasswd->clear();
//    }


//    if(m_dbManager && m_dbManager->checkLogin(username, password)){
//        if(ui->linePasswd->text() == m_passWord){
//            //ui->label->setText("登陆成功");
//            emit sendMessage("登陆成功");
//            emit loginSuccess();
//        }else{
//           // ui->label->setText("密码错误");
//            emit sendMessage("密码错误");
//            ui->linePasswd->clear();
//        }
//    }else{
//        //ui->label->setText("用户名错误");
//        emit sendMessage("用户名错误");
//        ui->lineUserName->clear();
//        ui->linePasswd->clear();
//    }
}

void CenterWidget::onRegister()
{
    emit requestRegister();
//    QString username = ui->lineUserName->text();
//    QString password = ui->linePasswd->text();

//    if (username.isEmpty() || password.isEmpty()) {
//        emit sendMessage("用户名和密码不能为空");
//        return;
//    }

//    if (m_dbManager && m_dbManager->registerUser(username, password)) {
//        emit sendMessage("注册成功");
//    } else {
//        emit sendMessage("注册失败，用户名已存在");
    //    }
}

void CenterWidget::showRegisterManager()
{
    // 清空输入框
    ui->lineUserName->clear();
    ui->linePasswd->clear();
}


void CenterWidget::loadStyleSheet(const QString &path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadWrite)){
        qDebug() << "css file open failed";
        return;
    }
    this->setStyleSheet(file.readAll());
}

//读取配置文件
QVariant CenterWidget::readIniSettings()
{
    QVariant a = m_Settings->value("UserInfo/username");
    QVariant b = m_Settings->value("UserInfo/password");
    return a;
}
//写入配置文件
void CenterWidget::writeIniSettings()
{
    m_Settings->setValue("UserInfo/username","lisi");
    m_Settings->setValue("UserInfo/password","abc123");
}

void CenterWidget::setDatabaseManager(DatabaseManager *dbManager)
{
    m_dbManager = dbManager;
}

CenterWidget::~CenterWidget()
{
    delete ui;
}




