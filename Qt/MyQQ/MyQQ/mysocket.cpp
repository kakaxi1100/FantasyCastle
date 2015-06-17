#include "mysocket.h"
#include <QString>
#include <QHostAddress>
#include <QDataStream>
#include <QIODevice>
#include <QDebug>
#include <QtEndian>
#include <iostream>
#include "myevent.h"
#include <memory>
#include "global.h"

using namespace std;

int MySocket::clientID = 0;

MySocket::MySocket(QObject *parent) :
    QObject(parent)
{
    myTcpSocket = new QTcpSocket(this);
    connect(myTcpSocket, SIGNAL(readyRead()),this, SLOT(socketRecv()));
    connect(myTcpSocket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(myTcpSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    connect(myTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError()));
}

MySocket::~MySocket()
{
    if(myTcpSocket != NULL)
    {
        delete myTcpSocket;
    }

    QMap<qint32, struct ClientInfo*>::const_iterator it = clientMap.cbegin();
    while(it != clientMap.cend())
    {
        delete it.value();
        ++it;
    }
}

MySocket* MySocket::instance = NULL;

MySocket* MySocket::getInstance()
{
    if(instance == NULL)
    {
        return new MySocket();
    }
    return instance;
}

bool MySocket::isConnected()
{
    return _isConnected;
}

void MySocket::setConnectType(int type)
{
    _connectType = type;
}

void MySocket::socketConnect(uint userID, QString password, QString ip, int port)
{
    qDebug()<<"socketConnect "<<userID<<"   "<<password<<"   "<<ip<<"   "<< port<<endl;
    if(isConnected() == false)
    {
        myTcpSocket->abort();//取消已经有的连接
        QHostAddress hostAddr(ip);
        myTcpSocket->connectToHost(hostAddr, port);
        addClient(userID, password);
    }else{
        if(_connectType == 1)
        {
            loginSendMsg();
        }else if(_connectType == 2)
        {
            regSendMsg();
        }
    }
//    if(myTcpSocket->isOpen() == false)
//    {
//        if(myTcpSocket->state() == QAbstractSocket::UnconnectedState)
//        {
//            myTcpSocket->abort();
//            QHostAddress hostAddr(ip);
//            myTcpSocket->connectToHost(hostAddr, port);
//            addClient(userID, password);
//        }
//    }
}

void MySocket::socketConnected()
{
     qDebug()<<"socketConnected";
     _isConnected = true;
     if(_connectType == 1)
     {
         loginSendMsg();
     }else if(_connectType == 2)
     {
         regSendMsg();
     }
}

void MySocket::socketDisconnected()
{
     qDebug()<<"socketDisconnected";
     _isConnected = false;
}

//struct Test
//{
//    int a;
//    char buf[100];
//};

void MySocket::loginSendMsg()
{
    qDebug()<<"logoin send msg start..........";
    QByteArray outblock;//输出缓冲区
    QDataStream sendout(&outblock, QIODevice::WriteOnly);
    sendout.setByteOrder(QDataStream::LittleEndian);

    struct LoginSend loginSend;
    memset(&loginSend, 0, sizeof(loginSend));
    loginSend.protocolID = 100;
//---------------第二版 传用户ID过去---------------------------------------------------------

    loginSend.userID = clientMap[0]->userID;
    const char *password = clientMap[0]->password.toStdString().data();
    strncpy(loginSend.password,password, strlen(password));

    sendout<<qint16(sizeof(loginSend));//先用ushort发长度过去
    sendout<< loginSend.protocolID;//再发协议ID过去
    sendout<<loginSend.userID;//再发用户ID过去
    sendout.writeRawData(loginSend.password, sizeof(loginSend.password));//最后发密码过去

    qDebug()<<loginSend.userID<<"  "<<loginSend.password;
    qint64 q =  myTcpSocket->write(outblock, sizeof(loginSend) + 2);//还要加上此消息长度
    qDebug()<<"send length:: "<<q;
    qDebug()<<"..............logoin send msg end";
//---------------第一版 传用户名字过去--------------------------------------------------------
/*    //注意必须转化一个 处理一个，不能都转化完后再处理，否则，所有的 数据都会是一个值
    //比如：
    //const char *userName = QString("Ares").toStdString().data();
    //const char *password = QString("123456")..toStdString().data();
    //cout<< userName <<"  " <<password << endl;
    //这时 userName = password = 123456；
    //必须这样处理
    //const char *userName = QString("Ares").toStdString().data();
    //cout<< userName;
    //const char *password = QString("123456")..toStdString().data();
    //cout<<"  " <<password << endl;
    //这时输出正确的值 : Ares 123456

    const char *userName = clientMap[0]->userName.toStdString().data();
    strncpy(loginSend.userName,userName, strlen(userName));
    const char *password = clientMap[0]->password.toStdString().data();
    strncpy(loginSend.password,password, strlen(password));
    QDataStream sendout(&outblock, QIODevice::WriteOnly);
    sendout.setByteOrder(QDataStream::LittleEndian);
//    sendout.setVersion(QDataStream::Qt_5_2);
    sendout<<qint16(sizeof(loginSend));//先用ushort发长度过去
    sendout<< loginSend.protocolID;
    sendout.writeRawData(loginSend.userName, sizeof(loginSend.userName));
    sendout.writeRawData(loginSend.password, sizeof(loginSend.password));

    qDebug()<<loginSend.userName<<"  "<<loginSend.password<<"  "<<strlen(loginSend.userName) + strlen(loginSend.password)<<endl;
    qint64 q =  myTcpSocket->write(outblock, sizeof(loginSend) + 2);//还要加上此消息长度
    qDebug()<<"send length:: "<<q;
    //outblock.resize(0);
*/
//----------------------for test----------------------------------
//----------------------"//"表示公用测试块-------------------------

//    QByteArray outblock;
//    QDataStream sendout(&outblock, QIODevice::WriteOnly);
//    sendout.setByteOrder(QDataStream::LittleEndian);
//    if(sendout.byteOrder() == sendout.BigEndian)
//    {
//        qDebug()<<"BigEndian";
//    }else{
//        qDebug()<<"LittleEndian";
//    }
 /*
//  注意char的类型的长度（sizeof）要提成int在后端才能正确收到
//  后端的类型也是int
//    int a = 123456;//转换成服务器的字节序
//    sendout<< a;
//    char b = 'x';
//    sendout<<b;
//    char c = 'y';
//    sendout<<c;
//    char d = 'z';
//    sendout<<d;
    const char * h = "okokokkok";
//    sendout << h; 这个服务端收到会错误，不知道输入成什么类型了
//    sendout.writeBytes(h, strlen(h)); 这个服务端收到会错误，内部经过处理了，用的无符号32位整型
//    outblock.append(h, strlen(h));
    sendout.writeRawData(h, strlen(h));//这个服务端收到不会报错
   qint64 q =  myTcpSocket->write(outblock, strlen(h));
*/
/*   //传结构体测试
   struct Test t;
   t.a = 10;
   memset(t.buf, 0, sizeof(t.buf));
   const char* b = "bb";
   qDebug()<<"strlen(b)  "<<strlen(b);
   strncpy(t.buf, b, strlen(b));
   qDebug()<<"t.buf  "<<strlen(t.buf);
   sendout<<t.a;
   //如果用QDataStream传字符传一定要用到这个，writeBtytes 传字符串会报错，否则就用QByteArray传字符串
   sendout.writeRawData(t.buf, strlen(t.buf));
   qint64 q =  myTcpSocket->write(outblock, sizeof(t.a) + strlen(t.buf));
*/
//   qDebug()<<q;

//----------------------------------------------------------------
}

void MySocket::regSendMsg()
{
    qDebug()<<"register send msg start..........";
    QByteArray outblock;//输出缓冲区
    QDataStream sendout(&outblock, QIODevice::WriteOnly);
    sendout.setByteOrder(QDataStream::LittleEndian);

    struct RegSend regSend;
    memset(&regSend, 0, sizeof(regSend));
    regSend.protocolID = 200;

    regSend.userID = clientMap[0]->userID;
    const char *password = clientMap[0]->password.toStdString().data();
    strncpy(regSend.password,password, strlen(password));

    sendout<<qint16(sizeof(regSend));//先用ushort发长度过去
    sendout<< regSend.protocolID;//再发协议ID过去
    sendout<<regSend.userID;//再发用户ID过去
    sendout.writeRawData(regSend.password, sizeof(regSend.password));//最后发密码过去

    qDebug()<<regSend.userID<<"  "<<regSend.password;
    qint64 q =  myTcpSocket->write(outblock, sizeof(regSend) + 2);//还要加上此消息长度
    qDebug()<<"send length:: "<<q;
    qDebug()<<"..............register send msg end";
}

void MySocket::socketRecv()
{
    if(myTcpSocket->bytesAvailable() < (int)sizeof(quint16))
    {
        qDebug()<<"bytesAvailable not enough !";
        return;
    }
    qDebug()<<"Recv len: "<<myTcpSocket->bytesAvailable();
    QDataStream in(myTcpSocket);
    in.setByteOrder(QDataStream::LittleEndian);
    ushort len = 0;
    ushort protocolID = 0;

    in>>len;
    in>>protocolID;
    qDebug()<<"protocol info: "<<len<<"  "<<protocolID;
    switch(protocolID)
    {
    case 101://--login recv
    {
        struct LoginRecv loginRecv;
        in>>loginRecv.loginType;
        shared_ptr<MyEvent> e_log;
        if(loginRecv.loginType == 0)
        {
            qDebug()<<"loginType Login Success!";
            e_log = make_shared<MyEvent>(LOGIN_RGE_SUCCESS);
            EventDispatcher<MyLogin>::dispatchEvent(e_log);
        }
        else if(loginRecv.loginType == 1)
        {
            qDebug()<<"loginType UserID Error!";
            e_log = make_shared<MyEvent>(LOGIN_RGE_FAILURE);
            EventDispatcher<MyLogin>::dispatchEvent(e_log);
        }
        else if(loginRecv.loginType == 2)
        {
            qDebug()<<"loginType Password Error!";
            e_log = make_shared<MyEvent>(LOGIN_RGE_FAILURE);
            EventDispatcher<MyLogin>::dispatchEvent(e_log);
        }
        else
        {
            qDebug()<<"loginType Unknown Error!";
        }
    }
        break;
    case 201://--register recv
    {
        struct RegRecv regRecv;
        in>>regRecv.regType;
        shared_ptr<MyEvent> e_reg;
        if(regRecv.regType == 0)
        {
            qDebug()<<"register Success!";
            e_reg = make_shared<MyEvent>(LOGIN_RGE_SUCCESS);
            EventDispatcher<MyLogin>::dispatchEvent(e_reg);
        }
        else if(regRecv.regType == 1)
        {
            qDebug()<<"register Error!";
            e_reg = make_shared<MyEvent>(LOGIN_RGE_FAILURE);
            EventDispatcher<MyLogin>::dispatchEvent(e_reg);
        }
    }
        break;
    default:
        break;
    }


    //------------for test------------------------
    /* QDataStream in(myTcpSocket);
    char buf[100] = {0};
    in.readRawData(buf, sizeof(buf));
    qDebug()<<"the message is: "<<buf;*/
    //--------------------------------------------
}

void MySocket::socketError()
{
    qDebug()<<myTcpSocket->errorString();
}

void MySocket::addClient(uint userID, QString password)
{
    struct ClientInfo* clientInfo = new ClientInfo();

    clientInfo->id = clientID;
    clientInfo->userID = userID;
//    clientInfo->userName = userName;
    clientInfo->password = password;

    clientMap[clientInfo->id] = clientInfo;

    clientID++;
}

