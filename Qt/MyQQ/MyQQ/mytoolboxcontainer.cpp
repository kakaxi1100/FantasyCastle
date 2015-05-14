#include "mytoolboxcontainer.h"
#include <QVBoxLayout>
#include <QGroupBox>

MyToolBoxContainer::MyToolBoxContainer(QWidget *parent) :
    QWidget(parent)
{
    //add defualt tool box
    myToolBox = new MyToolBox(this);

    QGroupBox * toolBtnCtn = new QGroupBox(myToolBox);

    QToolButton * tb1 = new QToolButton(toolBtnCtn);
    tb1->setText("User 1");
    tb1->setAutoRaise(true);

    QToolButton * tb2 = new QToolButton(toolBtnCtn);
    tb2->setText("User 2");
    tb2->setAutoRaise(true);

    QVBoxLayout *vbox = new QVBoxLayout(toolBtnCtn);
    vbox->addWidget(tb1);
    vbox->addWidget(tb2);
    vbox->addStretch();

    myToolBox->addItem(toolBtnCtn, "My Friends");
}
