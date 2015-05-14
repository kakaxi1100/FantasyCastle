#ifndef MYLOGIN_H
#define MYLOGIN_H

#include <QWidget>

#include <QLineEdit>
#include <QPushButton>
#include "mywidget.h"

class MyLogin : public QWidget
{
    Q_OBJECT
public:
    explicit MyLogin(QWidget *parent = 0);

private slots:
    void loginClick();
    void cancelClick();
    void regClick();
private:
    QLineEdit* account;
    QLineEdit* password;
    QPushButton* login;
    QPushButton* cancel;
    QPushButton* reg;

    MyWidget* myqq;
};

#endif // MYLOGIN_H
