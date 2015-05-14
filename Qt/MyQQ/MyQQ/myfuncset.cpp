#include "myfuncset.h"
#include <QDebug>

MyFuncSet::MyFuncSet(QWidget *parent) :
    QWidget(parent)
{
    addFriendBtn = new QPushButton(this);
    addFriendBtn->setText("Add");
    settingBtn = new QPushButton(this);
    settingBtn->setText("Setting");

    btnContainer = new QHBoxLayout(this);
    btnContainer->addWidget(addFriendBtn);
    btnContainer->addWidget(settingBtn);
    btnContainer->addStretch();

    connect(addFriendBtn, SIGNAL(clicked()), this, SLOT(addFriendBtnClick()));
    connect(settingBtn, SIGNAL(clicked()), this, SLOT(settingBtnClick()));

    //myAddFirend dialog
    myAddFriend = new MyAddFriend();
}

void MyFuncSet::addFriendBtnClick()
{
    if(myAddFriend->isHidden() == true)
    {
        myAddFriend->show();
    }
    else
    {
        qDebug()<< "myAddFriend is show" << endl;
    }
}

void MyFuncSet::settingBtnClick()
{

}
