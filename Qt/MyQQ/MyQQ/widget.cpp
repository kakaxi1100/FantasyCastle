#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    mylogin = new MyLogin(this);
}

bool Widget::eventFilter(QObject *object, QEvent *event)
{
    if(object == mylogin)
    {
        qDebug()<<"It's me";
        return true;
    }

    return QWidget::eventFilter(object, event);
}


Widget::~Widget()
{

}
