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
    password = new QLineEdit(this);

    login = new QPushButton(this);
    login->setText("login");

    cancel = new QPushButton(this);
    cancel->setText("cancel");

    reg = new QPushButton(this);
    reg->setText("reg");

    QLabel* al = new QLabel(this);
    al->setText("account:");

    QLabel* pl = new QLabel(this);
    pl->setText("password:");

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

    QVBoxLayout* v1 = new QVBoxLayout(this);
    v1->addLayout(h1);
    v1->addLayout(h2);
    v1->addLayout(h3);

    connect(login, SIGNAL(clicked()),this, SLOT(loginClick()));
    connect(cancel, SIGNAL(clicked()),this, SLOT(cancelClick()));
    connect(reg, SIGNAL(clicked()),this, SLOT(regClick()));

    //myqq
    myqq = new MyWidget();
}

void MyLogin::loginClick()
{
    qDebug()<<"login clicked!"<<endl;
    if(myqq->isHidden() == true)
    {
        myqq->show();
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
}
