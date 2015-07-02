#include "mywidget.h"
#include <QDebug>
#include <QPixmap>
#include "myevent.h"
#include "mytoolbutton.h"

//int MyWidget::clientID = 0;
struct ClientInfo MyWidget::myInfo;

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{
    this->resize(200,600);

    //tool boxs
    mytoolbox = new MyToolBox();
    //add myfriend
    friendGroup = new QGroupBox();
    friendVBox = new QVBoxLayout(friendGroup);
    friendVBox->setMargin(10);
    friendVBox->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    //    friendVBox->addStretch(1);
    //add blacklist
    blackListGroup = new QGroupBox();
    blackListVBox = new QVBoxLayout(blackListGroup);
    blackListVBox->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    blackListVBox->setMargin(10);

    mytoolbox->addItem(friendGroup, "My Friend");
    mytoolbox->addItem(blackListGroup, "Black List");

    //func set
    myFunSet = new MyFuncSet();

    testBtn = new QPushButton(this);
    testBtn->setText("test");

    QVBoxLayout* mainVBox = new QVBoxLayout(this);
    mainVBox->addWidget(mytoolbox);
    mainVBox->addWidget(myFunSet);
    mainVBox->addWidget(testBtn);

    connect(testBtn, SIGNAL(clicked()), this,SLOT(testFunc()));

    //event
//    shared_ptr<MyWidget> t(this);
//    EventDispatcher<MyWidget>::addEventListener(ADD_FRIEND, t, &MyWidget::addFriendItem);
}

MyWidget::~MyWidget()
{
    QMap<qint32, struct ClientInfo*>::const_iterator it = clientMap.cbegin();
    while(it != clientMap.cend())
    {
        delete it.value();
        ++it;
    }

    qDebug()<<"~MyWidget()";
}


void MyWidget::addClient(ClientInfo &c)
{
     struct ClientInfo* clientInfo = new ClientInfo();
//     clientInfo->id = clientID;
     clientInfo->userID = c.userID;
     clientInfo->userName = c.userName;
     clientInfo->userImage = c.userImage;
     clientInfo->userState = c.userState;

     clientMap[clientInfo->userID] = clientInfo;

     qDebug()<<"[clientInfo]: userID: " << clientInfo->userID << " ImageID: " << clientInfo->userImage << " Name: " << clientInfo->userName <<" State: " << clientInfo->userState << endl;
}

void MyWidget::destroyObjs()
{
//    EventDispatcher<MyWidget>::removeEventListener(ADD_FRIEND);
}

void MyWidget::testFunc()
{
    qDebug() << "testFunc::" <<endl;
//    addFriendItem();
    addBlckListItem();
}

void MyWidget::addFriendItem(ClientInfo& c)
{
    qDebug() << "addFriendItem：：" <<endl;

    MyToolButton* t = new MyToolButton();
    t->setClientInfo(c);
    friendVBox->addWidget(t);
}

void MyWidget::addBlckListItem()
{
    qDebug() << "addBlckListItem::" <<endl;
    MyToolButton* t = new MyToolButton();
    t->setText(tr("ray"));
    t->setIcon(QPixmap(":/root/headNormal/2.png"));
    t->setIconSize(QPixmap(":/root/headNormal/2.png").size());
    t->setAutoRaise(true);
    t->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    blackListVBox->addWidget(t);
}
