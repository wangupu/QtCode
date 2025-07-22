#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>


class DatabaseManager : public QWidget
{
    Q_OBJECT
public:
    explicit DatabaseManager(QWidget *parent = nullptr);
    bool initDatabase();
    bool checkLogin(const QString &username, const QString &password);
    bool registerUser(const QString &username, const QString &password);

};

#endif // DATABASEMANAGER_H
