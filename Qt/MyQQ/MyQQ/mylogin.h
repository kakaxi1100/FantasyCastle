#ifndef MYLOGIN_H
#define MYLOGIN_H

#include <QWidget>

#include <QLineEdit>
#include <QPushButton>
#include <QMap>
#include "global.h"
#include "mysocket.h"
#include <vector>
#include <unordered_map>
#include "myeventdispatcher.h"
#include "mywidget.h"

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

//    QMap<int, struct ClientInfo*> clientMap;
//    static int clientID;

//    void addClient(quint32 userID);//添加用户信息
//    void addClient(struct ClientInfo& c);
//    void addClient(quint32 userID, QString userName, qint32 userImage, qint8 userState);
private:
    qint8 whichBtn;
public:
    void destroyObjs();
    void enableBtns(bool _isCan);

    void handleLoginSuccess(MyEvent &e);
    void handleLoginFailure(MyEvent &e);
    void handleSokectConnected(MyEvent &e);
    void handleFriendListRecv(MyEvent &e);
public:
    vector<vector<unordered_map<string, string> > > parseString(string& test);
};

#endif // MYLOGIN_H
