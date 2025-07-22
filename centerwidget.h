#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QSettings>
#include "databasemanager.h"

namespace Ui {
class CenterWidget;
}

class CenterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CenterWidget(QWidget *parent = nullptr);
    ~CenterWidget();

    void loadStyleSheet(const QString &);

    QVariant readIniSettings();
    void writeIniSettings();

    void setDatabaseManager(DatabaseManager* dbManager);

signals:
    void sendMessage(const QString &);
    void display(int);
    void loginSuccess();
    void requestRegister();

public slots:
    void onLogin();
    void onRegister();
    void showRegisterManager();

private:
    Ui::CenterWidget *ui;
    QString m_userName;
    QString m_passWord;
    QTimer *m_pTimer;
    QSettings * m_Settings;
    DatabaseManager* m_dbManager = nullptr;
};

#endif // CENTERWIDGET_H
