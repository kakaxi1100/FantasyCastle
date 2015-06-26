#include "mychat.h"
#include <QLocale>
#include <QHBoxLayout>
#include <QVBoxLayout>

MyChat::MyChat(QWidget *parent) :
    QWidget(parent)
{
    this->resize(588, 512);

    showText = new QTextBrowser(this);
//    showText->setGeometry(10,10,566,290);

    inputText = new QTextEdit(this);
//    inputText->setGeometry(10,320,566,80);

    closeBtn = new QPushButton();
    closeBtn->setText("Close");
    sendBtn = new QPushButton();
    sendBtn->setText("Send");

    QVBoxLayout* v1 = new QVBoxLayout();
    v1->addWidget(showText, 6);
    v1->addWidget(inputText, 2);
//    v1->addStretch(3);

    QHBoxLayout* h1 = new QHBoxLayout();
    h1->addWidget(closeBtn, 0);
    h1->addWidget(sendBtn, 0);
    h1->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
//    h1->addStretch();

    QVBoxLayout* v2 = new QVBoxLayout(this);
    v2->addLayout(v1);
    v2->addLayout(h1);
}
