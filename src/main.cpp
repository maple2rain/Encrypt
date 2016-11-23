#include "../include/mainwindow.h"
#include <QApplication>
#include <QTableWidget>
#include "../include/playfair.h"
#include "../include/rsa.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(555, 520);
    w.show();
    return a.exec();
}
