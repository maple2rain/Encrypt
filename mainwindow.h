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

private:
    typedef enum encryptType{//加密算法类型选择枚举
        NONE, PLAYFAIR, HILL
    }encryptType;

public:
    explicit MainWindow(QWidget *parent = 0, encryptType option = NONE);
    ~MainWindow();
    void choosePlayfair(void){
        options = PLAYFAIR;
    }

    void chooseHill(void){
        options = HILL;
    }

    void encryptPlayfair(void);//playfair加密算法
    void deEncryptPlayfair(void);//playfair解密算法
    void encryptHill(void);//Hill加密算法
    void deEncryptHill(void);//Hill解密算法
    void showEncrypt(void);//显示加密结果
    void showDeEncrypt(void);//显示解密结果
    void showMatrix(void);//显示矩阵
    void showPlayfairMatrix(void);//显示playfair矩阵
    void showHillMatrix(void);//显示Hill矩阵
    void closeMatrix(void);//关闭矩阵

private:
    encryptType options;//加密算法选择
    Ui::MainWindow *ui;
    QRadioButton *Playfair;//选择playfair算法的单项按钮
    QRadioButton *Hill;//选择hill算法的单项按钮
    QTextEdit *textClear;
    QTextEdit *textCipher;
    QLineEdit *textKey;
    PlayFair *playfair;
    PlayTable *playtable;
};

#endif // MAINWINDOW_H
