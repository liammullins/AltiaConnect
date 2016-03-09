#include "mainwindow.h"
#include <QApplication>

/* public staticFileController - move me*/


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow main_win;
    main_win.showMaximized();

    return a.exec();
}
