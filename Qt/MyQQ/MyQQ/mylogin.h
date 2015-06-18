#ifndef MYLOGIN_H
#define MYLOGIN_H

#include <QWidget>

#include <QLineEdit>
#include <QPushButton>
#include <QMap>
#include "mysocket.h"
#include "mywidget.h"

struct ClientInfo
{
    qint32 id;
    uint userID;
    QString userName;
    QString password;
};


class MyLogin : public QWidget
{
    Q_OBJECT
public:
    explicit MyLogin(QWidget *parent = 0);
    ~MyLogin();
private slots:
    void loginClick();
    void cancelClick();
    void regClick();
protected:
    void closeEvent(QCloseEvent *);
private:
    QLineEdit* account;
    QLineEdit* password;
    QLineEdit* hostIP;
    QLineEdit* hostPort;
    QPushButton* login;
    QPushButton* cancel;
    QPushButton* reg;

    MySocket* mysocket;
    MyWidget* myqq;

    QMap<int, struct ClientInfo*> clientMap;
    static int clientID;
    void addClient(uint userID, QString password);//添加用户信息
private:
    qint8 whichBtn;
public:
    void destroyObjs();
    void enableBtns(bool _isCan);

    void handleLoginSuccess(MyEvent &e);
    void handleLoginFailure(MyEvent &e);
    void handleSokectConnected(MyEvent &e);
};

#endif // MYLOGIN_H
