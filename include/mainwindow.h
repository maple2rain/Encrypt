#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QRadioButton>
#include <QDebug>
#include "table.h"
#include "playfair.h"
#include "hill.h"
#include "strdeal.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    enum encryptType{//加密算法类型选择枚举
        NONE, PLAYFAIR, HILL
    };

/* 使用异或运算来表示设置读写文件标志,
 * 其中,读为二进制1，不读为0，写为1，不写为0
 * 读标志在第0位，写标志在第1位
 */
#define READ_MASK  0x01
#define WRITE_MASK 0x02
    
public:
    explicit MainWindow(QWidget *parent = 0, encryptType option = NONE, unsigned char flag = 0);
    ~MainWindow();

    void choosePlayfair(void);//选择playfair算法
    void chooseHill(void);//选择Hill算法
    void checkReadFile(void);//检测按钮判断是否从文件中读取
    void checkWriteFile(void);//检测按钮判断是否将数据写入文件
    void openFile(QTextEdit *text);//打开文件
    void saveFile(QTextEdit *text);//关闭文件
    bool isReadFromFile(void) { return (rwFileFlag & READ_MASK) == READ_MASK; }//判断是否从文件中读取
    bool isWriteToFile(void) { return (rwFileFlag & WRITE_MASK) == WRITE_MASK; }//判断是否写入文件

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
    unsigned char rwFileFlag;//读写文件标志

    Ui::MainWindow  *ui;
    QRadioButton    *Playfair;//选择playfair算法的单项按钮
    QRadioButton    *Hill;//选择hill算法的单项按钮
    QTextEdit       *textClear;
    QTextEdit       *textCipher;
    QLineEdit       *textKey;
    PlayFair        *playfair;
    HillEnc         *hill;
    PlayTable       *playtable;
};

inline
void MainWindow::checkReadFile(){
    rwFileFlag ^= READ_MASK;
}

inline
void MainWindow::checkWriteFile(){
    rwFileFlag ^= WRITE_MASK;
}

#endif // MAINWINDOW_H
