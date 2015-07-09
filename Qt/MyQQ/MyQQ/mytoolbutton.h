#ifndef MYTOOLBUTTON_H
#define MYTOOLBUTTON_H

#include <QToolButton>
#include "global.h"
#include "mychat.h"
#include "myeventdispatcher.h"
#include "myevent.h"

class MyToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit MyToolButton(QWidget *parent = 0);
    ~MyToolButton();

    void setClientInfo(ClientInfo &c);
    ClientInfo& getClientInfo();

    void showReceiverChat(QString name, QString msg);
public slots:
    void handleClicked();
protected:

private:
    ClientInfo clientInfo;
    MyChat* myChat;
};

#endif // MYTOOLBUTTON_H
