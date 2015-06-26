#ifndef MYTOOLBUTTON_H
#define MYTOOLBUTTON_H

#include <QToolButton>
#include "global.h"

class MyToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit MyToolButton(QWidget *parent = 0);

    void setClientInfo(ClientInfo &c);
    ClientInfo& getClientInfo();
public slots:
    void handleClicked();
protected:

private:
    ClientInfo clientInfo;
};

#endif // MYTOOLBUTTON_H
