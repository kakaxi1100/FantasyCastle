#ifndef MYFUNCSET_H
#define MYFUNCSET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "myaddfriend.h"

class MyFuncSet : public QWidget
{
    Q_OBJECT
public:
    explicit MyFuncSet(QWidget *parent = 0);

signals:

private slots:
    void addFriendBtnClick();
    void settingBtnClick();
private:
    QPushButton* addFriendBtn;
    QPushButton* settingBtn;
    QHBoxLayout* btnContainer;
    MyAddFriend* myAddFriend;
};

#endif // MYFUNCSET_H
