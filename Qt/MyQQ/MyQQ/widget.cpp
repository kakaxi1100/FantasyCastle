#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    mylogin = new MyLogin();
    mylogin->show();
}
//bool Widget::eventFilter(QObject *object, QEvent *event)
//{
//    if(object == mylogin)
//    {
//        qDebug()<<"It's me";
//        return true;
//    }

//    if(event->type() == QEvent::Close)
//    {
//        qDebug()<<"hahahahahahahhaaha";
//    }

//    return QWidget::eventFilter(object, event);
//}


Widget::~Widget()
{
    qDebug()<<"~Widget()";
}

void Widget::closeEvent(QCloseEvent *)
{
    mylogin->destroyObjs();
}
