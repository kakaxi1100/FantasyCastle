#include "widget.h"
#include "mywidget.h"
#include "mylogin.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    MyWidget w;
    MyLogin w;
    w.show();

    return a.exec();
}
