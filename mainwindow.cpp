#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QRadioButton>
#include <QLabel>
#include <QGroupBox>
#include "playfair.h"
#include "table.h"
#include "strdeal.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *widget = new QWidget(this);
    this->setCentralWidget(widget);
    setWindowTitle("PalyFair");

    QPushButton *encryptBtn = new QPushButton(tr("加密"), this);//设置显示矩阵按钮
    connect(encryptBtn, &QPushButton::clicked, this, &MainWindow::showEncrypt);
    QPushButton *deEncryptBtn = new QPushButton(tr("解密"), this);
    connect(deEncryptBtn, &QPushButton::clicked, this, &MainWindow::showDeEncrypt);
    QPushButton *showInfo = new QPushButton(tr("显示额外信息"));
    connect(showInfo, &QPushButton::clicked, this, &MainWindow::showMatrix);
    QPushButton *closeInfo = new QPushButton(tr("关闭额外信息"));
    connect(closeInfo, &QPushButton::clicked, this, &MainWindow::closeMatrix);

    textKey = new QLineEdit(this);//设置密钥读取文本框
    textClear = new QTextEdit(this);//设置明文读取文本框
    textCipher = new QTextEdit(this);//设置密文读取文本框

    playtable = new PlayTable(this);//构建表格

    /* 显示右侧方框 */
    QLabel *clearText = new QLabel(tr("明文"), widget);
    QLabel *keyText = new QLabel(tr( "密钥" ), widget);
    QLabel *cipherText = new QLabel(tr("密文"));

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(keyText, 0, 0, Qt::AlignRight);
    grid->addWidget(textKey, 0, 1, Qt::AlignLeft);
    grid->addWidget(clearText, 1, 0, Qt::AlignRight);
    grid->addWidget(textClear, 1, 1, Qt::AlignLeft);
    grid->addWidget(cipherText, 2, 0, Qt::AlignRight);
    grid->addWidget(textCipher, 2, 1, Qt::AlignLeft);

    QHBoxLayout *showHbox = new QHBoxLayout(this);
    showHbox->addWidget(playtable);
    QGroupBox *show = new QGroupBox(tr("显示额外信息"));
    show->setLayout(showHbox);
    QGroupBox *operationGBox = new QGroupBox(tr("操作"), this);//添加组布局
    operationGBox->setLayout(grid);

    QVBoxLayout *operAndShow = new QVBoxLayout(this);
    operAndShow->addWidget(operationGBox);
    operAndShow->addWidget(show);

    /* 显示单项按钮 */
    Playfair = new QRadioButton("Playfair", this);
    Hill = new QRadioButton("Hill", this);
    QHBoxLayout *radioBtnHbox = new QHBoxLayout(this);
    radioBtnHbox->addWidget(Playfair, 1, Qt::AlignLeft);
    radioBtnHbox->addWidget(Hill, 1, Qt::AlignLeft);

    QGroupBox *radioBtnGBox = new QGroupBox(tr("加密算法"), this);
    radioBtnGBox->setLayout(radioBtnHbox);

    /* 添加加密和解密按钮 */
    QGridLayout *funChoseGlot = new QGridLayout(this);
    QGroupBox *funChoseGBox = new QGroupBox(tr("按钮"), this);
    funChoseGlot->addWidget(encryptBtn, 0, 0);
    funChoseGlot->addWidget(deEncryptBtn, 0, 1);
    funChoseGlot->addWidget(showInfo, 1, 0);
    funChoseGlot->addWidget(closeInfo, 1, 1);
    funChoseGBox->setLayout(funChoseGlot);

    /* 为单项按钮和加密解密按钮添加垂直布局 */
    QVBoxLayout *funAndChoseVBox = new QVBoxLayout(this);
    funAndChoseVBox->addWidget(radioBtnGBox);
    funAndChoseVBox->addWidget(funChoseGBox);

    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->addLayout(funAndChoseVBox);
    hbox->addLayout(operAndShow);
    widget->setLayout(hbox);

    playtable->close();
}

MainWindow::~MainWindow()
{
    //delete ui;
    //delete showAction;
    if(!playfair)
        delete playfair;
    if(!textKey)
        delete textKey;
    if(!textClear)
        delete textClear;
    if(!Hill)
        delete Hill;
    if(!textCipher)
        delete textCipher;
    if(!playtable)
        delete playtable;
}

void MainWindow::showMatrix()
{
    if(!playfair)
        delete playfair;
    string textkey = QStoStr(textKey->text());
    qDebug() << StrtoQSt(textkey);
    letterFilter(textkey);
    qDebug() << "string is";
    qDebug() << StrtoQSt(textkey);
    playfair = new PlayFair(textkey);

    qDebug() << "begin to create table";
    playtable->AddItem(*playfair);
    qDebug() << "end of creating table";
    playtable->show();
}

void MainWindow::closeMatrix()
{
    playtable->close();
}

void MainWindow::showEncrypt()
{

}

void MainWindow::showDeEncrypt()
{

}
