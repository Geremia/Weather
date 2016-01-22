#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    a.setOrganizationName("Geremia");
    a.setApplicationName("Weather");

    return a.exec();
}
