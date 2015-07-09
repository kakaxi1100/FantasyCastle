#include "mywidget.h"
#include <QDebug>
#include <QPixmap>
#include "myevent.h"
#include "messagerecvevent.h"

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
    shared_ptr<MyWidget> t(this);
    EventDispatcher<MyWidget>::addEventListener(MSG_RECV, t, &MyWidget::handleRecvMsg);
//    EventDispatcher<MyWidget>::addEventListener(ADD_FRIEND, t, &MyWidget::addFriendItem);
}

MyWidget::~MyWidget()
{
//    EventDispatcher<MyWidget>::removeEventListener(MSG_RECV);
    QMap<unsigned int, struct ClientInfo*>::const_iterator it = clientMap.cbegin();
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
      EventDispatcher<MyWidget>::removeEventListener(MSG_RECV);
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
//    t->setAccessibleName(QString::number(c.userID));
//    t->setObjectName(QString::number(c.userID));
    toolBtns[c.userID] = t;
    qDebug()<<t->objectName();
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

void MyWidget::handleRecvMsg(MyEvent &e)
{
   MessageRecvEvent& event = (MessageRecvEvent&) e;
   qDebug()<<QString(QLatin1String(e.getType().c_str()));
   qDebug()<<"senderUserID: "<<event.senderUserID<<" receiverUserID "<<event.receiverUserID<<endl;
   if(event.senderUserID == myInfo.userID)
   {
       //假如发送者是自己
       //找到收信人
//       MyToolButton* recv = friendVBox->findChild<MyToolButton*>(QString::number(event.receiverUserID));
       MyToolButton* recv = toolBtns[event.receiverUserID];
       if(recv == NULL)
       {
            qDebug()<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
           return;
       }
       //假如找到了收信人则显示消息
       //temp中的client 信息已经保存了发信人的信息
       recv->showReceiverChat(myInfo.userName,QString(QLatin1String(event.messge.c_str())));
       return;
   }

    //如果发信者是别人
   //先查找有没有发信人
//   MyToolButton* temp = friendVBox->findChild<MyToolButton*>(QString::number(event.senderUserID));
   MyToolButton* temp = toolBtns[event.senderUserID];
   if(temp == NULL)
   {
       return;
   }

   //假如找到了收信人则显示消息
   //temp中的client 信息已经保存了发信人的信息
   temp->showReceiverChat(temp->getClientInfo().userName, QString(QLatin1String(event.messge.c_str())));
}
