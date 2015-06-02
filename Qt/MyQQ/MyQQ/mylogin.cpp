#include "mylogin.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

MyLogin::MyLogin(QWidget *parent) :
    QWidget(parent)
{
   // this->setWindowFlags(Qt::FramelessWindowHint);

    account = new QLineEdit(this);
    account->setText("10000");
    password = new QLineEdit(this);
    password->setText("123456");
    hostIP = new QLineEdit(this);
    hostIP->setText("10.88.52.79");
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
    mysocket = new MySocket();
}

void MyLogin::loginClick()
{
    qDebug()<<"login clicked!"<<endl;
//    if(myqq->isHidden() == true)
//    {
//        myqq->show();
//    }

    mysocket->socketConnect(account->text().toUInt(), password->text(),hostIP->text(), hostPort->text().toInt());
}

void MyLogin::cancelClick()
{
    qDebug()<<"cancel clicked!"<<endl;
    this->close();
}

void MyLogin::regClick()
{
    qDebug()<<"reg clicked!"<<endl;
}
