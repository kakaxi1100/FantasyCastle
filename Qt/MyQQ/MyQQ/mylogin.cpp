#include "mylogin.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QLatin1String>
#include "myevent.h"
#include "friendlistevent.h"
#include "loginregevent.h"

MyLogin::MyLogin(QWidget *parent) :
    QWidget(parent)
{
   // this->setWindowFlags(Qt::FramelessWindowHint);

    account = new QLineEdit(this);
    account->setText("10004");
    password = new QLineEdit(this);
    password->setText("123456");
    hostIP = new QLineEdit(this);
    hostIP->setText("10.88.52.88");
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

    qDebug()<<"~MyLogin()";
}

void MyLogin::handleFriendListRecv(MyEvent &e)
{
    FriendListEvent& event = (FriendListEvent&) e;
    //解析字符串
    vector<vector<unordered_map<string, string>>> valueVec = parseString(event.list);
    qDebug()<<"valueVec:::::::::::::: "<< valueVec.size() << endl;
    for(auto v : valueVec)//v = vec
    {
        ClientInfo c;
        for (auto m : v)//m = map
        {
            for (auto p : m)//p = pair
            {
                qDebug()<< QString(QLatin1String(p.first.c_str()))<< " = " << QString(QLatin1String(p.second.c_str())) << endl;
                if(p.first == "ID")
                {
                    c.userID = atoi(p.second.c_str());
                }
                else if(p.first == "IMAGE")
                {
                    c.userImage = atoi(p.second.c_str());
                }else if(p.first == "NAME")
                {
                    c.userName = QString(QLatin1String (p.second.c_str()));
                }else if(p.first == "STATE")
                {
                    c.userState = atoi(p.second.c_str());
                }
            }
        }
        myqq->addClient(c);
        myqq->addFriendItem(c);
//        shared_ptr<MyEvent> e_addf = make_shared<MyEvent>(ADD_FRIEND);
//        EventDispatcher<MyWidget>::dispatchEvent(e_addf);
    }
}


//解析字符串
//{ID:10000, NAME:cccc, IMAGE:1, STATE:0}, {ID:10001, NAME:bbbbb, IMAGE:2, STATE:1}
//取得每个字段对应的值
vector<vector<unordered_map<string, string>>> MyLogin::parseString(string &test)
{
    vector<unordered_map<string, string>> tempVec;

    string::size_type left = 0;
    string::size_type right = 0;

    vector<vector<unordered_map<string, string>>> finalVec;

    while (true)
    {
        left = test.find_first_of('{', left);
        right = test.find_first_of('}', right);

        if (left == string::npos || right == string::npos)
        {
            break;
        }

        string temp = test.substr(left + 1, right - left - 1);
        //cout << temp << endl;

        string::size_type lpos = 0;
        string::size_type rpos = 0;
        string item;

        string::size_type kpos = 0;
        string key;
        string value;
        while (true)
        {
            unordered_map<string, string> tempMap;
            rpos = temp.find_first_of(',', rpos);
            if (rpos == string::npos)
            {
                item = temp.substr(lpos);
                kpos = item.find_first_of(':');
                key = item.substr(0, kpos);
                value = item.substr(kpos + 1);
                //cout << "[ " << key << " ] = " << value << endl;
                tempMap[key] = value;
                tempVec.push_back(tempMap);
                break;
            }
            item = temp.substr(lpos, rpos - lpos);
            kpos = item.find_first_of(':');
            key = item.substr(0, kpos);
            value = item.substr(kpos + 1);
            //cout << "[ " << key << " ] = " << value << endl;
            tempMap[key] = value;
            ++rpos;
            lpos = rpos;
            tempVec.push_back(tempMap);
        }

        ++right;
        left = right;
        finalVec.push_back(tempVec);
    }
    return finalVec;
}

void MyLogin::handleSokectConnected(MyEvent &e)
{
    qDebug()<<QString(QLatin1String(e.getType().c_str()))<<endl;
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
    qDebug()<<QString(QLatin1String(e.getType().c_str()))<<endl;
    enableBtns(true);
}

void MyLogin::handleLoginSuccess(MyEvent& e)
{
    qDebug()<<QString(QLatin1String(e.getType().c_str()))<<endl;
    LoginRegEvent& evt = (LoginRegEvent&)e;
    enableBtns(true);
    if(myqq->isHidden() == true)
    {
        vector<vector<unordered_map<string, string>>> valueVec = parseString(evt.list);
        for(auto m : valueVec[0])
        {
            for(auto p : m)
            {
                if(p.first == "ID")
                {
                    MyWidget::myInfo.userID = atoi(p.second.c_str());
                }
                else if(p.first == "IMAGE")
                {
                    MyWidget::myInfo.userImage = atoi(p.second.c_str());
                }else if(p.first == "NAME")
                {
                    MyWidget::myInfo.userName = QString(QLatin1String (p.second.c_str()));
                }
            }
        }

        MyWidget::myInfo.userState = 1;
        mysocket->friendListSendMsg(MyWidget::myInfo.userID);

        myqq->show();
        this->hide();
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


//在父对象响应关闭事件之前调用， 先销毁对象
void MyLogin::destroyObjs()
{
    myqq->destroyObjs();

    EventDispatcher<MyLogin>::removeEventListener(LOGIN_RGE_SUCCESS);
    EventDispatcher<MyLogin>::removeEventListener(LOGIN_RGE_FAILURE);
    EventDispatcher<MyLogin>::removeEventListener(SOCKET_CONNECTED);
    EventDispatcher<MyLogin>::removeEventListener(FRIEND_LIST);
}
