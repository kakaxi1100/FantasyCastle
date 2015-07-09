#include "mytoolbutton.h"
#include "mywidget.h"
#include <QDebug>

MyToolButton::MyToolButton(QWidget *parent) :
    QToolButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(handleClicked()));
    myChat = NULL;
}

MyToolButton::~MyToolButton()
{
    delete myChat;
}

void MyToolButton::setClientInfo(ClientInfo &c)
{
    this->clientInfo = c;

    this->setText(clientInfo.userName);

    this->setIcon(QPixmap(":/root/headNormal/1.png"));
    this->setIconSize(QPixmap(":/root/headNormal/1.png").size());
    this->setAutoRaise(true);
    if(c.userState == 0)
    {
        this->setEnabled(false);
    }else{
        this->setEnabled(true);
    }
    this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

ClientInfo &MyToolButton::getClientInfo()
{
    return this->clientInfo;
}

void MyToolButton::showReceiverChat(QString name, QString msg)
{
     qDebug()<<"The Chat user is : "<<this->clientInfo.userName;
    //add my chat
    if(myChat == NULL)
    {
        qDebug()<<"create new chat!";
        myChat = new MyChat(this->clientInfo);
    }
    if(myChat->isHidden())
    {
        myChat->show();
    }

    myChat->showMsg(name, msg);
}


void MyToolButton::handleClicked()
{
    qDebug()<<"The Chat user is : "<<this->clientInfo.userName;
    //add my chat
    if(myChat == NULL)
    {
        qDebug()<<"create new chat!";
        myChat = new MyChat(this->clientInfo);
    }
    if(myChat->isHidden())
    {
        myChat->show();
    }
}
