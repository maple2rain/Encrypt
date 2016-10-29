#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QRadioButton>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QGroupBox>
#include <QMessageBox>
#include <QFileDialog>
#include "playfair.h"
#include "table.h"
#include "strdeal.h"

MainWindow::MainWindow(QWidget *parent, encryptType option, unsigned char flag) :
    QMainWindow(parent), options(option), rwFileFlag(flag)
{
    QWidget *widget = new QWidget(this);
    this->setCentralWidget(widget);
    this->setWindowTitle("Encryption");
    this->setWindowIcon(QIcon("images/icon.png"));

    QPushButton *encryptBtn = new QPushButton(tr("Encrypt"), this);//设置显示矩阵按钮
    connect(encryptBtn, &QPushButton::clicked, this, &MainWindow::showEncrypt);
    QPushButton *deEncryptBtn = new QPushButton(tr("Decrypt"), this);
    connect(deEncryptBtn, &QPushButton::clicked, this, &MainWindow::showDeEncrypt);
    QPushButton *showInfo = new QPushButton(tr("More Info"));
    connect(showInfo, &QPushButton::clicked, this, &MainWindow::showMatrix);
    QPushButton *closeInfo = new QPushButton(tr("Close Info"));
    connect(closeInfo, &QPushButton::clicked, this, &MainWindow::closeMatrix);

    QCheckBox *readFile = new QCheckBox(tr("Read From File"), this);
    connect(readFile, &QCheckBox::stateChanged, this, &MainWindow::checkReadFile);
    QCheckBox *writeFile = new QCheckBox(tr("Write To File"), this);
    connect(writeFile, &QCheckBox::stateChanged, this, &MainWindow::checkWriteFile);

    textKey = new QLineEdit(this);//设置密钥读取文本框
    textClear = new QTextEdit(this);//设置明文读取文本框
    textCipher = new QTextEdit(this);//设置密文读取文本框

    playtable = new PlayTable(this);//构建表格

    /* 显示右侧方框 */
    QLabel *clearText = new QLabel(tr("Clear Text"), widget);
    QLabel *keyText = new QLabel(tr( "Key" ), widget);
    QLabel *cipherText = new QLabel(tr("Cipher Text"));

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(keyText, 0, 0, Qt::AlignRight);
    grid->addWidget(textKey, 0, 1);
    grid->addWidget(clearText, 1, 0, Qt::AlignRight);
    grid->addWidget(textClear, 1, 1);
    grid->addWidget(cipherText, 2, 0, Qt::AlignRight);
    grid->addWidget(textCipher, 2, 1);

    QHBoxLayout *showHbox = new QHBoxLayout(this);
    showHbox->addWidget(playtable);
    QGroupBox *show = new QGroupBox(tr("More Info"));
    show->setLayout(showHbox);
    QGroupBox *operationGBox = new QGroupBox(tr("Operation"), this);//添加组布局
    operationGBox->setLayout(grid);

    QVBoxLayout *operAndShow = new QVBoxLayout(this);
    operAndShow->addWidget(operationGBox);
    operAndShow->addWidget(show);

    /* 显示单项按钮 */
    Playfair = new QRadioButton("Playfair", this);
    Hill = new QRadioButton("Hill", this);
    connect(Playfair, &QRadioButton::clicked, this, &MainWindow::choosePlayfair);
    connect(Hill, &QRadioButton::clicked, this, &MainWindow::chooseHill);

    QHBoxLayout *radioBtnHbox = new QHBoxLayout(this);
    radioBtnHbox->addWidget(Playfair, 1, Qt::AlignLeft);
    radioBtnHbox->addWidget(Hill, 1, Qt::AlignLeft);

    QGroupBox *radioBtnGBox = new QGroupBox(tr("Algorithm Frame"), this);
    radioBtnGBox->setLayout(radioBtnHbox);

    /* 添加读取文件可选项 */
    QVBoxLayout *rwOptVBox = new QVBoxLayout(this);
    rwOptVBox->addWidget(readFile);
    rwOptVBox->addWidget(writeFile);
    QGroupBox *rwOptGBox = new QGroupBox(tr("Options"));
    rwOptGBox->setLayout(rwOptVBox);

    /* 添加加密和解密按钮 */
    QGridLayout *funChoseGlot = new QGridLayout(this);
    QGroupBox *funChoseGBox = new QGroupBox(tr("Button"), this);
    funChoseGlot->addWidget(encryptBtn, 0, 0);
    funChoseGlot->addWidget(deEncryptBtn, 0, 1);
    funChoseGlot->addWidget(showInfo, 1, 0);
    funChoseGlot->addWidget(closeInfo, 1, 1);
    funChoseGBox->setLayout(funChoseGlot);

    /* 设置关于标签 */
    QLabel *aboutLbl = new QLabel(
                "This simple program was completed by Maple."
                "For more infomation, please visit the author's "
                "<a href = \"http://blog.leanote.com/maple2snow\">Home Page</a>.",
                this);
    aboutLbl->setTextFormat(Qt::RichText);
    aboutLbl->setTextInteractionFlags(Qt::TextBrowserInteraction);
    aboutLbl->setOpenExternalLinks(true);
    aboutLbl->setWordWrap(true);
    aboutLbl->setAlignment(Qt::AlignTop);

    QVBoxLayout *aboutVBox = new QVBoxLayout(this);
    aboutVBox->addWidget(aboutLbl);
    QGroupBox *aboutGBox = new QGroupBox(tr("About"), this);
    aboutGBox->setLayout(aboutVBox);

    /* 为单项按钮、加密解密按钮、多选框、关于添加垂直布局 */
    QVBoxLayout *funAndChoseVBox = new QVBoxLayout(this);
    funAndChoseVBox->addWidget(radioBtnGBox);
    funAndChoseVBox->addWidget(rwOptGBox);
    funAndChoseVBox->addWidget(funChoseGBox);
    funAndChoseVBox->addWidget(aboutGBox);


    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->addLayout(funAndChoseVBox);
    hbox->addLayout(operAndShow);
    widget->setLayout(hbox);

    playtable->close();
    playfair = new PlayFair;
    hill = new HillEnc;
}

MainWindow::~MainWindow()
{
    if(!playfair)
        delete playfair;
    if(!Hill)
        delete Hill;
    if(!playtable)
        delete playtable;
}

void MainWindow::showPlayfairMatrix(void)
{
    if(textKey->isModified()){
        string textkey = QStoStr(textKey->text());
        qDebug() << StrtoQSt(textkey);
        letterFilter(textkey);//过滤密钥非字母
        qDebug() << "string is";
        qDebug() << StrtoQSt(textkey);
        if(!playfair){
            delete playfair;
            playfair = nullptr;
        }
        playfair = new PlayFair(textkey);
    }

    /* 添加实例填充表格并显示 */
    playtable->AddItem(*playfair);
    playtable->show();
}

void MainWindow::showHillMatrix(void)
{
    if(textKey->isModified()){
        string textkey = QStoStr(textKey->text());
        letterFilter(textkey);//将密钥过滤非字母

        if(!hill){
            delete hill;
            hill = nullptr;
        }

        if(textkey.empty())
            hill = new HillEnc;
        else
            hill = new HillEnc(textkey);

        if(!hill->available()){
            QMessageBox::warning(this, tr("Warning"), tr("You did not input an valid key."));
            return ;
        }
    }

    /* 添加实例填充表格并显示 */
    playtable->AddItem(*hill);
    playtable->show();
}

void MainWindow::showMatrix(void)
{
    switch (options) {
    case PLAYFAIR:
        showPlayfairMatrix();
        break;
    case HILL:
        showHillMatrix();
        break;
    default:
        qDebug() << "don't choose any algorithm";
        QMessageBox::warning(this, tr("Warning"), tr("You did not choose any algorithm."));
        break;
    }
}

void MainWindow::closeMatrix(void)
{
    playtable->close();
}

void MainWindow::showEncrypt(void)
{
    if(isReadFromFile())
        openFile(textClear);

    switch(options){
    case PLAYFAIR:
        encryptPlayfair();
        break;
    case HILL:
        encryptHill();
        break;
    default:
        qDebug() << "don't choose any algorithm";
        QMessageBox::warning(this, tr("Warning"), tr("You did not choose any algorithm."));
        break;
    }

    if(isWriteToFile())
        saveFile(textCipher);
}

void MainWindow::showDeEncrypt(void)
{
    if(isReadFromFile())
        openFile(textCipher);

    switch (options) {
    case PLAYFAIR:
        deEncryptPlayfair();
        break;
    case HILL:
        deEncryptHill();
        break;
    default:
        qDebug() << "don't choose any algorithm";
        QMessageBox::warning(this, tr("Warning"), tr("You did not choose any algorithm."));
        break;
    }

    if(isWriteToFile())
        saveFile(textClear);
}

void MainWindow::encryptPlayfair(void)
{
    string encryptText = QStoStr(textClear->toPlainText());
    if(encryptText.empty()){
        QMessageBox::warning(this, tr("Warning"), tr("You didn't input the clear text."));
        return ;
    }

    if(textKey->isModified()){
        if(!playfair){
            delete playfair;
            playfair = nullptr;
        }

        string textkey = QStoStr(textKey->text());
        letterFilter(textkey);
        playfair = new PlayFair(textkey);

        /* 添加实例填充表格并显示 */
        playtable->AddItem(*playfair);
    }

    /* 加密及显示 */
    playfair->encrypt(encryptText);
    textCipher->setText(StrtoQSt(encryptText));

}

void MainWindow::deEncryptPlayfair(void)
{
    string DeEncryptText = QStoStr(textCipher->toPlainText());
    if(DeEncryptText.empty()){
        QMessageBox::warning(this, tr("Warning"), tr("You didn't input the cipher text."));
        return ;
    }

    if(textKey->isModified()){
        if(!playfair){
            delete playfair;
            playfair = nullptr;
        }

        string textkey = QStoStr(textKey->text());
        letterFilter(textkey);
        playfair = new PlayFair(textkey);

        /* 添加实例填充表格并显示 */
        playtable->AddItem(*playfair);
    }

    /* 解密及显示 */
    playfair->deEncrypt(DeEncryptText);
    textClear->setText(StrtoQSt(DeEncryptText));
}

void MainWindow::encryptHill(void)
{
    string encryptText = QStoStr(textClear->toPlainText());
    if(encryptText.empty()){
        QMessageBox::warning(this, tr("Warning"), tr("You didn't input the clear text."));
        return ;
    }

    if(textKey->isModified()){
        string textkey = QStoStr(textKey->text());
        letterFilter(textkey);

        if(!hill){
            delete hill;
            hill = nullptr;
        }

        if(textkey.empty())
            hill = new HillEnc;
        else
            hill = new HillEnc(textkey);

        if(!hill->available()){
            QMessageBox::warning(this, tr("Warning"), tr("You did not input an valid key."));
            return ;
        }
    }

    /* 加密及显示 */
    hill->encrypt(encryptText);
    textCipher->setText(StrtoQSt(encryptText));
}

void MainWindow::deEncryptHill(void)
{
    string deEncryptText = QStoStr(textCipher->toPlainText());
    if(deEncryptText.empty()){
        QMessageBox::warning(this, tr("Warning"), tr("You didn't input the cipher text."));
        return ;
    }

    if(textKey->isModified()){
        if(!hill){
            delete hill;
            hill = nullptr;
        }

        string textkey = QStoStr(textKey->text());
        letterFilter(textkey);//过滤密钥非字母

        if(textkey.empty())
            hill = new HillEnc;
        else
            hill = new HillEnc(textkey);

        if(!hill->available()){
            QMessageBox::warning(this, tr("Warning"), tr("You did not input an valid key."));
            return ;
        }
    }

    /* 解密及显示 */
    hill->deEncrypt(deEncryptText);
    textClear->setText(StrtoQSt(deEncryptText));
}

void MainWindow::choosePlayfair(){
    options = PLAYFAIR;
    textKey->setText(tr(""));
    textKey->setDisabled(false);
    playtable->close();
}

inline
void MainWindow::chooseHill(){
    options = HILL;
    textKey->setText(tr("rrfvsvcct"));
    textKey->setDisabled(true);
    playtable->close();
}

void MainWindow::openFile(QTextEdit *text)
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.txt)"));//打开文件路径，使用this为当前父窗口，“Open File”为对话框标题，“.”为默认目录，过滤器为“Text Files(*.txt)”
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {//以只读方式打开text文件
            QMessageBox::warning(this, tr("Read File"), tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream in(&file);//打开文件输入流
        text->setText(in.readAll());//读取文本内容，当超过100M时程序会崩溃
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
    }
}

void MainWindow::saveFile(QTextEdit *text)
{
    if(text->document()->isEmpty()) return;
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Text Files(*.txt)"));//与打开文件同理
    if(!path.isEmpty()) {
        QFile file(path);//读取路径
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write File"), tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);//打开文件输出流
        out << text->toPlainText();//输出到文件
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
    }
}
