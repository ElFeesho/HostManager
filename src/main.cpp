#include <QtGui/QApplication>

#include "hostmanagerapplication.hpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("HostManager");
    a.setQuitOnLastWindowClosed(false);
    new HostManagerApplication(&a);
    return a.exec();
}
