#include "mylogin.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include "myeventdispatcher.h"
#include "global.h"
#include "myevent.h"
#include "friendlistevent.h"


int MyLogin::clientID = 0;

MyLogin::MyLogin(QWidget *parent) :
    QWidget(parent)
{
   // this->setWindowFlags(Qt::FramelessWindowHint);

    account = new QLineEdit(this);
    account->setText("10004");
    password = new QLineEdit(this);
    password->setText("123456");
    hostIP = new QLineEdit(this);
    hostIP->setText("10.88.52.79");
//    hostIP->setText("192.168.1.254");
    hostPort = new QLineEdit(this);
    hostPort->setText("8080");

    login = new QPushButton(this);
    login->setText("login");

    cancel = new QPushButton(this);
    cancel->setText("cancel");

    reg = new QPushButton(this);
    reg->setText("reg");

    QLabel* al = new QLabel(this);
    al->setText("Account:");

    QLabel* pl = new QLabel(this);
    pl->setText("Password:");

    QLabel* ipl = new QLabel(this);
    ipl->setText("Host IP:");

    QLabel* portl = new QLabel(this);
    portl->setText("Host Port:");

    QHBoxLayout* h1 = new QHBoxLayout();
    h1->addWidget(al);
    h1->addWidget(account);

    QHBoxLayout* h2 = new QHBoxLayout();
    h2->addWidget(pl);
    h2->addWidget(password);

    QHBoxLayout* h3 = new QHBoxLayout();
    h3->addWidget(login);
    h3->addWidget(cancel);
    h3->addWidget(reg);

    QHBoxLayout* h4 = new QHBoxLayout();
    h4->addWidget(ipl);
    h4->addWidget(hostIP);

    QHBoxLayout* h5 = new QHBoxLayout();
    h5->addWidget(portl);
    h5->addWidget(hostPort);

    QVBoxLayout* v1 = new QVBoxLayout(this);
    v1->addLayout(h1);
    v1->addLayout(h2);
    v1->addLayout(h4);
    v1->addLayout(h5);
    v1->addLayout(h3);

    connect(login, SIGNAL(clicked()),this, SLOT(loginClick()));
    connect(cancel, SIGNAL(clicked()),this, SLOT(cancelClick()));
    connect(reg, SIGNAL(clicked()),this, SLOT(regClick()));

    //myqq
    myqq = new MyWidget();
    //socket
    mysocket = MySocket::getInstance();

    //event
    shared_ptr<MyLogin> t(this);
    EventDispatcher<MyLogin>::addEventListener(LOGIN_RGE_SUCCESS, t, &MyLogin::handleLoginSuccess);
    EventDispatcher<MyLogin>::addEventListener(LOGIN_RGE_FAILURE, t, &MyLogin::handleLoginFailure);
    EventDispatcher<MyLogin>::addEventListener(SOCKET_CONNECTED, t, &MyLogin::handleSokectConnected);
    EventDispatcher<MyLogin>::addEventListener(FRIEND_LIST, t, &MyLogin::handleFriendListRecv);
}

MyLogin::~MyLogin()
{
    //和Qt不兼容
    //关掉窗口的时候，会delete掉它，shared_ptr引用消失时又delete一遍，会造成问题.
    //暂时没有办法解决
    //找到了解决办法，在父对象关闭之前先调用mylogin的removeeventlisent方法，让mylogin析构
    //当父对象发现mylogin已经析构时，就不在delete mylogin
//    EventDispatcher<MyLogin>::removeEventListener(LOGIN_RGE_SUCCESS);
//    EventDispatcher<MyLogin>::removeEventListener(LOGIN_RGE_FAILURE);
//    EventDispatcher<MyLogin>::removeEventListener(SOCKET_CONNECTED);

    QMap<qint32, struct ClientInfo*>::const_iterator it = clientMap.cbegin();
    while(it != clientMap.cend())
    {
        delete it.value();
        ++it;
    }
    qDebug()<<"~MyLogin()";
}

void MyLogin::handleFriendListRecv(MyEvent &e)
{
    FriendListEvent& event = (FriendListEvent&) e;

}

void MyLogin::handleSokectConnected(MyEvent &e)
{
    cout<<e.getType()<<endl;
    if(whichBtn == 1)//login
    {
        mysocket->loginSendMsg(account->text().toUInt(), password->text());
    }
    else if(whichBtn == 2)//reg
    {
        mysocket->regSendMsg(account->text().toUInt(), password->text());
    }

    whichBtn = 0;
}

void MyLogin::handleLoginFailure(MyEvent& e)
{
    cout<< e.getType() <<endl;
    enableBtns(true);
}

void MyLogin::handleLoginSuccess(MyEvent& e)
{
    cout<< e.getType() <<endl;
    enableBtns(true);
    if(myqq->isHidden() == true)
    {
        addClient(account->text().toUInt(), password->text());
        mysocket->friendListSendMsg(clientMap[0]->userID);

//        myqq->show();
//        this->hide();
    }
}

void MyLogin::loginClick()
{
    qDebug()<<"login clicked!"<<endl;
    enableBtns(false);
    whichBtn = 1;
    if(mysocket->isConnected())
    {
        mysocket->loginSendMsg(account->text().toUInt(), password->text());
    }else{
        mysocket->socketConnect(hostIP->text(), hostPort->text().toInt());//链接服务器
    }
}

void MyLogin::cancelClick()
{
    qDebug()<<"cancel clicked!"<<endl;
    this->close();
}

void MyLogin::regClick()
{
    qDebug()<<"reg clicked!"<<endl;
    enableBtns(false);
    whichBtn = 2;
    cout<<mysocket->isConnected()<<endl;
    if(mysocket->isConnected())
    {
        mysocket->regSendMsg(account->text().toUInt(), password->text());
    }else{
        mysocket->socketConnect(hostIP->text(), hostPort->text().toInt());
    }
}

void MyLogin::closeEvent(QCloseEvent *)
{
    destroyObjs();
}

void MyLogin::enableBtns(bool _isCan)
{
    account->setEnabled(_isCan);
    password->setEnabled(_isCan);
    hostIP->setEnabled(_isCan);
    hostPort->setEnabled(_isCan);
    login->setEnabled(_isCan);
    reg->setEnabled(_isCan);
}

void MyLogin::addClient(quint32 userID, QString password)
{
    struct ClientInfo* clientInfo = new ClientInfo();

    clientInfo->id = clientID;
    clientInfo->userID = userID;
//    clientInfo->userName = userName;
    clientInfo->password = password;

    clientMap[clientInfo->id] = clientInfo;

    clientID++;
}

//在父对象响应关闭事件之前调用， 先销毁对象
void MyLogin::destroyObjs()
{
    EventDispatcher<MyLogin>::removeEventListener(LOGIN_RGE_SUCCESS);
    EventDispatcher<MyLogin>::removeEventListener(LOGIN_RGE_FAILURE);
    EventDispatcher<MyLogin>::removeEventListener(SOCKET_CONNECTED);
    EventDispatcher<MyLogin>::removeEventListener(FRIEND_LIST);
}
