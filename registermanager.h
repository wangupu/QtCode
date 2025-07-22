#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H

#include <QWidget>

namespace Ui {
class RegisterManager;
}

class RegisterManager : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterManager(QWidget *parent = nullptr);
    ~RegisterManager();

signals:
    void returnToLogin();

private:
    Ui::RegisterManager *ui;
};

#endif // REGISTERMANAGER_H
