#include "mytoolbutton.h"
#include <QDebug>

MyToolButton::MyToolButton(QWidget *parent) :
    QToolButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(handleClicked()));
}

void MyToolButton::setClientInfo(ClientInfo &c)
{
    this->clientInfo = c;

    this->setText(clientInfo.userName);

    this->setIcon(QPixmap(":/root/headNormal/1.png"));
    this->setIconSize(QPixmap(":/root/headNormal/1.png").size());
    this->setAutoRaise(true);
    this->setEnabled(false);
    this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

ClientInfo &MyToolButton::getClientInfo()
{
    return this->clientInfo;
}

void MyToolButton::handleClicked()
{
    qDebug()<<this->clientInfo.userName;
}
