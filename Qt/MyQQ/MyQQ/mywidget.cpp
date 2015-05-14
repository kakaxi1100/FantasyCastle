#include "mywidget.h"
#include <QDebug>
#include <QToolButton>
#include <QPixmap>

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
}

void MyWidget::testFunc()
{
    qDebug() << "testFunc::" <<endl;
    addFriendItem();
    addBlckListItem();
}

void MyWidget::addFriendItem()
{
    qDebug() << "addFriendItem：：" <<endl;
    QToolButton* t = new QToolButton();
    t->setText(tr("Ares"));
    t->setIcon(QPixmap(":/root/headNormal/1.png"));
    t->setIconSize(QPixmap(":/root/headNormal/1.png").size());
    t->setAutoRaise(true);
    t->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    friendVBox->addWidget(t);
}

void MyWidget::addBlckListItem()
{
    qDebug() << "addBlckListItem::" <<endl;
    QToolButton* t = new QToolButton();
    t->setText(tr("ray"));
    t->setIcon(QPixmap(":/root/headNormal/2.png"));
    t->setIconSize(QPixmap(":/root/headNormal/2.png").size());
    t->setAutoRaise(true);
    t->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    blackListVBox->addWidget(t);
}
