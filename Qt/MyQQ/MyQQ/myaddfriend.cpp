#include "myaddfriend.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

MyAddFriend::MyAddFriend(QWidget *parent) :
    QWidget(parent)
{
    QWidget* upArea = new QWidget(this);
    findBtn = new QPushButton();
    findBtn->setText("Find");
    addBtn = new QPushButton();
    addBtn->setText("Add");
    numberLE = new QLineEdit();

    QLabel* numberLB = new QLabel();
    numberLB->setText("Number：");

    QHBoxLayout* h1 = new QHBoxLayout();
    h1->addWidget(numberLB);
    h1->addWidget(numberLE);

    QHBoxLayout* h2 = new QHBoxLayout();
    h2->addWidget(findBtn);
    h2->addWidget(addBtn);

    QVBoxLayout* v1 = new QVBoxLayout(upArea);
    v1->addLayout(h1);
    v1->addLayout(h2);

    infoTE = new QTextEdit(this);

    QGridLayout* mainLY = new QGridLayout(this);
    mainLY->addWidget(upArea, 0,0,1,1);
    mainLY->addWidget(infoTE, 1,0,1,1);
}
