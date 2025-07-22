#include "databasemanager.h"

DatabaseManager::DatabaseManager(QWidget *parent) : QWidget(parent)
{
    initDatabase();
}

//初始化数据库
bool DatabaseManager::initDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("UserInfo.db");

    if (!db.open()) {
        qDebug() << "无法打开数据库:" << db.lastError();
        return false;
    }

    // 创建用户表(如果不存在)
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                   "username TEXT PRIMARY KEY, "
                   "password TEXT)")) {
        qDebug() << "创建表失败:" << query.lastError();
        return false;
    }

    return true;
}

//对比数据库中的用户名和密码 检查登录
bool DatabaseManager::checkLogin(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = ?");
    query.addBindValue(username);

    if (!query.exec()) {
        qDebug() << "查询失败:" << query.lastError();
        return false;
    }

    if (query.next()) {
        QString correctPassword = query.value(0).toString();
        return (correctPassword == password);
    }

    return false;
}

//注册新用户
bool DatabaseManager::registerUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);

    if (!query.exec()) {
        qDebug() << "注册失败:" << query.lastError();
        return false;
    }

    return true;
}

