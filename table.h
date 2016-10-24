#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QTableWidget>
#include "playfair.h"

class PlayFair;

class PlayTable : public QTableWidget{
public:
    PlayTable(QWidget *parent = 0);
    PlayTable(int rows = 0, int cols = 0, QWidget *parent = 0) :
        QTableWidget(rows, cols, parent){}

    void AddItem(char *array);
    void AddItem(PlayFair &playfair);
};

#endif // TABLE_H
