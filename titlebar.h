#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include "statusShelper.h"

namespace Ui {
class TitleBar;
}

class TitleBar : public QWidget {
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();

    void loadStyleSheet(const QString &);

signals:
    void showWidgetStatus(int);

public slots:
    void onMiniSized();
    void onMaxSized();
    void onClose();

private:
    Ui::TitleBar *ui;
    bool m_isMaxSized = false;
};

#endif // TITLEBAR_H
