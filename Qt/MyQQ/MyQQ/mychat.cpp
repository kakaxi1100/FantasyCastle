#include "mychat.h"
#include <QLocale>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStringList>
#include <QSize>
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>
#include <QColorDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "mywidget.h"

#define MAX_CHAR 2048
MyChat::MyChat(ClientInfo &c, QWidget* parent):QWidget(parent)
{
    this->clientInfo = c;

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
    fontHomeBox->setEditable(false);

    fontSizeBox = new QComboBox();
    QStringList sizeList;
    sizeList<<"9"<<"10"<<"11"<<"12"<<"13"<<"14"<<"15"<<"16"<<"17"<<"18"<<"19"<<"20"<<"21"<<"22";
    fontSizeBox->insertItems(0, sizeList);
    fontSizeBox->setCurrentIndex(3);

    boldToolBtn = new QToolButton();
    boldToolBtn->setCheckable(true);//可以按下
    boldToolBtn->setIcon(QIcon(":/root/chatIcon/bold.png"));
    boldToolBtn->setIconSize(QSize(32,32));
    boldToolBtn->setAutoRaise(true);

    italicToolBtn = new QToolButton();
    italicToolBtn->setCheckable(true);
    italicToolBtn->setIcon(QIcon(":/root/chatIcon/italic.png"));
    italicToolBtn->setIconSize(QSize(32,32));
    italicToolBtn->setAutoRaise(true);

    underlineToolBtn = new QToolButton();
    underlineToolBtn->setCheckable(true);
    underlineToolBtn->setIcon(QIcon(":/root/chatIcon/underline.png"));
    underlineToolBtn->setIconSize(QSize(32,32));
    underlineToolBtn->setAutoRaise(true);

    colorToolBtn = new QToolButton();
    colorToolBtn->setIcon(QIcon(":/root/chatIcon/color.png"));
    colorToolBtn->setIconSize(QSize(32,32));
    colorToolBtn->setAutoRaise(true);

    sendToolBtn = new QToolButton();
    sendToolBtn->setIcon(QIcon(":/root/chatIcon/sendfile.png"));
    sendToolBtn->setIconSize(QSize(32,32));
    sendToolBtn->setAutoRaise(true);

    saveToolBtn = new QToolButton();
    saveToolBtn->setIcon(QIcon(":/root/chatIcon/savemsg.png"));
    saveToolBtn->setIconSize(QSize(32,32));
    saveToolBtn->setAutoRaise(true);

    clearToolBtn = new QToolButton();
    clearToolBtn->setIcon(QIcon(":/root/chatIcon/clearmsg.png"));
    clearToolBtn->setIconSize(QSize(32,32));
    clearToolBtn->setAutoRaise(true);

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
    connect(fontHomeBox, SIGNAL(currentFontChanged(QFont)), this, SLOT(fontHomeChange()));
    connect(fontSizeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(fontSizeChange()));
    connect(boldToolBtn, SIGNAL(clicked(bool)), this, SLOT(fontBoldChange()));
    connect(italicToolBtn, SIGNAL(clicked(bool)), this, SLOT(fontItalicChange()));
    connect(underlineToolBtn, SIGNAL(clicked(bool)), this, SLOT(fontUnderlineChange()));
    connect(colorToolBtn, SIGNAL(clicked()), this,SLOT(colorBtnClicked()));
    connect(saveToolBtn, SIGNAL(clicked()), this, SLOT(saveBtnClicked()));
    connect(clearToolBtn, SIGNAL(clicked()), this, SLOT(clearBtnClicked()));
    //当单击输入框中一个字体时，字体格式设置会变成设置这个字体时的设置
    connect(inputText, SIGNAL(currentCharFormatChanged(QTextCharFormat)), this, SLOT(fontFormatChanged(const QTextCharFormat)));

    mySocket = MySocket::getInstance();
}

//bool MyChat::eventFilter(QObject *o, QEvent *e)
//{
//    qDebug()<<e->type();
//    if(e->type()==QEvent::Quit)
//    {
//        qDebug()<<"close chat window.";
//        this->hide();
//        return true;//不想让它继续转发就写true 否则写 false
//    }

//    return QWidget::eventFilter(o, e);
//}

//void MyChat::closeEvent(QCloseEvent *e)
//{
//    this->hide();
//}

void MyChat::sendMsg()
{
    if(inputText->toPlainText() == "")
    {
        QMessageBox::warning(this, "Warning", "Cannot send the empty content !", QMessageBox::Ok);
    }else{
        if(inputText->toHtml().length() >= MAX_CHAR)
        {
            QMessageBox::warning(this, "Warning", "The Message is too long !", QMessageBox::Ok);
            return;
        }

        mySocket->SendMessageSendMsg(MyWidget::myInfo.userID,this->clientInfo.userID, inputText->toHtml());
    }
}

void MyChat::closeClicked()
{
//    this->hide();
    this->close();
}

void MyChat::fontHomeChange()
{
    const QFont& f = fontHomeBox->currentFont();
    qDebug()<<f.toString();
    inputText->setFontFamily(f.toString());
    inputText->setFocus();
}

void MyChat::fontSizeChange()
{
    double s = fontSizeBox->currentText().toDouble();
    inputText->setFontPointSize(s);
    inputText->setFocus();
}

void MyChat::fontBoldChange()
{
    if(boldToolBtn->isChecked())
    {
        inputText->setFontWeight(QFont::Bold);
    }else
    {
        inputText->setFontWeight(QFont::Normal);
    }
    inputText->setFocus();
}

void MyChat::fontItalicChange()
{
    inputText->setFontItalic(italicToolBtn->isChecked());
    inputText->setFocus();
}

void MyChat::fontUnderlineChange()
{
    inputText->setFontUnderline(underlineToolBtn->isChecked());
    inputText->setFocus();
}

void MyChat::colorBtnClicked()
{
    color = QColorDialog::getColor(color,this);
    if(color.isValid())
    {
        inputText->setTextColor(color);
        inputText->setFocus();
    }
}

void MyChat::saveBtnClicked()
{
    if(showText->document()->isEmpty())
    {
        QMessageBox::warning(this, "Warning", "There is no chat Message, Can not save !", QMessageBox::Ok);
    }else{
        QString fileName = QFileDialog::getOpenFileName(this, "Save Chat Message.", "Chat Message", "Text(*.txt);;All File(*.*)");
        if(!fileName.isEmpty())
        {
            saveFile(fileName);
        }
    }
}

void MyChat::clearBtnClicked()
{
    showText->clear();
}

void MyChat::fontFormatChanged(const QTextCharFormat &format)
{
    fontHomeBox->setCurrentFont(format.font());

    if(format.fontPointSize() < 9)
    {
        fontSizeBox->setCurrentIndex(3);
    }else{
        fontSizeBox->setCurrentIndex(fontSizeBox->findText(QString::number(format.fontPointSize())));
    }

    boldToolBtn->setChecked(format.font().bold());
    italicToolBtn->setChecked(format.font().italic());
    underlineToolBtn->setChecked(format.font().underline());

    color = format.foreground().color();
}

void MyChat::showMsg()
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    showText->setTextColor(Qt::blue);
    showText->setCurrentFont(QFont("Arial", 12));
    showText->append("[ name ] "+time);
    showText->append(inputText->toHtml());
//    showText->verticalScrollBar()->setValue(showText->verticalScrollBar()->maximum());
    inputText->clear();
    inputText->setFocus();
}

bool MyChat::saveFile(QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Can not save file.", tr("Can not save %1 :\n %2").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out<<showText->toPlainText();
    return true;
}


