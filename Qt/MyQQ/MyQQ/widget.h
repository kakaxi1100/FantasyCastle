#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mylogin.h"
#include <QCloseEvent>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
//    bool eventFilter(QObject *object, QEvent *event);
    void closeEvent(QCloseEvent *);
private:
    MyLogin* mylogin;
};

#endif // WIDGET_H
