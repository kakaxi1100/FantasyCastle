#ifndef MYTOOLBOXCONTAINER_H
#define MYTOOLBOXCONTAINER_H

#include <QWidget>
#include "mytoolbox.h"
#include <QToolButton>

class MyToolBoxContainer : public QWidget
{
    Q_OBJECT
public:
    explicit MyToolBoxContainer(QWidget *parent = 0);

signals:

public slots:

private:
    MyToolBox* myToolBox;
};

#endif // MYTOOLBOXCONTAINER_H
