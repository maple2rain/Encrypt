#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QRadioButton>
#include "table.h"
#include "playfair.h"
#include "strdeal.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QRadioButton *Playfair;//选择playfair算法的单项按钮
    QRadioButton *Hill;//选择hill算法的单项按钮
    QTextEdit *textClear;
    QTextEdit *textCipher;
    QLineEdit *textKey;
    PlayFair *playfair;
    PlayTable *playtable;
public:
    void showEncrypt();
    void showDeEncrypt();
    void showMatrix();
    void closeMatrix();
};

#endif // MAINWINDOW_H
