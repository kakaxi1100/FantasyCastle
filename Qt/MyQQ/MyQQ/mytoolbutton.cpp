#include "mytoolbutton.h"
#include <QDebug>

MyToolButton::MyToolButton(QWidget *parent) :
    QToolButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(handleClicked()));
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
    }
    this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

ClientInfo &MyToolButton::getClientInfo()
{
    return this->clientInfo;
}

void MyToolButton::handleClicked()
{
    qDebug()<<this->clientInfo.userName;
    if(myChat == NULL)
    {
        myChat = new MyChat(this->clientInfo);
    }
    if(myChat->isHidden())
    {
        myChat->show();
    }
}
