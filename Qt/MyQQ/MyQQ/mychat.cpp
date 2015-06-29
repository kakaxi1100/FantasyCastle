#include "mychat.h"
#include <QLocale>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStringList>

MyChat::MyChat(QWidget *parent) :
    QWidget(parent)
{
    this->resize(588, 512);

    showText = new QTextBrowser();
//    showText->setGeometry(10,10,566,290);

    inputText = new QTextEdit();
//    inputText->setGeometry(10,320,566,80);

    closeBtn = new QPushButton();
    closeBtn->setText("Close");
    sendBtn = new QPushButton();
    sendBtn->setText("Send");

    fontHomeBox = new QFontComboBox();
    fontSizeBox = new QComboBox();
    QStringList sizeList;
    sizeList<<"9"<<"10"<<"11"<<"12"<<"13"<<"14"<<"15"<<"16"<<"17"<<"18"<<"19"<<"20"<<"21"<<"22";
    fontSizeBox->insertItems(0, sizeList);

    boldToolBtn = new QToolButton();
    italicToolBtn = new QToolButton();
    underlineToolBtn = new QToolButton();
    colorToolBtn = new QToolButton();
    sendToolBtn = new QToolButton();
    saveToolBtn = new QToolButton();
    clearToolBtn = new QToolButton();

    QHBoxLayout* h2 = new QHBoxLayout();
    h2->addWidget(fontHomeBox);
    h2->addWidget(fontSizeBox);
    h2->addWidget(boldToolBtn);
    h2->addWidget(italicToolBtn);
    h2->addWidget(underlineToolBtn);
    h2->addWidget(colorToolBtn);
    h2->addWidget(sendToolBtn);
    h2->addWidget(saveToolBtn);
    h2->addWidget(clearToolBtn);

    QVBoxLayout* v1 = new QVBoxLayout();
    v1->addWidget(showText, 6);
    v1->addLayout(h2);
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

    connect(sendBtn,SIGNAL(clicked()), this, SLOT(sendMsg()));
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(closeClicked()));
}

void MyChat::sendMsg()
{
    showText->append("what the hell ?");
}

void MyChat::closeClicked()
{
    this->hide();
}


