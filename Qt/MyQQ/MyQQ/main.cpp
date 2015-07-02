#include "widget.h"
#include "mywidget.h"
#include "mylogin.h"
#include "mychat.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
//    MyWidget w;
//    MyLogin w;
//    MyChat w;
//    w.show();
    return a.exec();
}
