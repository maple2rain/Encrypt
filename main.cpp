#include "mainwindow.h"
#include <QApplication>
#include <QTableWidget>
#include "playfair.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(555, 520);
    w.show();
    return a.exec();
}
