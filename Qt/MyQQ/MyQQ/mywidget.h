#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "myaddfriend.h"
#include "myfuncset.h"
#include "mytoolbox.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);

private slots:
    void testFunc();
private:
    MyToolBox *mytoolbox;
    QGroupBox* friendGroup;
    QVBoxLayout* friendVBox;
    QGroupBox* blackListGroup;
    QVBoxLayout* blackListVBox;

    MyFuncSet* myFunSet;

    QPushButton* testBtn;

    void addFriendItem();
    void addBlckListItem();
};

#endif // MYWIDGET_H
