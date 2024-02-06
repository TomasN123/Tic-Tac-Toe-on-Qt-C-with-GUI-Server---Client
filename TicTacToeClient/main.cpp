#include "menu.h"
#include <QMovie>
#include <QThread>


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menu w;
    w.show();
    return a.exec();
}
