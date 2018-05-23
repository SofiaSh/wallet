#include "walletwindow.h"
#include "firstdialog.h"
#include "logindialog.h"
#include "transaction.h"
#include <fstream>
#include <io.h>
#include <fstream>
#include <time.h>
#include <sstream>
#include <QDateTime>
WalletWindow::WalletWindow(QWidget *parent) : QWidget(parent)
{
    if(_access("wallet.txt",0))
    {
        FirstDialog *window1=new FirstDialog();
        window1->show();
    }
    else
    {
        LoginDialog *window=new LoginDialog();
        window->show();
        connect(window, SIGNAL(IDSignal(std::string&)), SLOT(IDSlot(std::string&)));
        connect(window, SIGNAL(closed()), SLOT(close()));
    }
    srand((int)time(NULL));
    timer= new QTimer();
    timer->setSingleShot(true);
    timer->setInterval(rand() % 60000);
    timer->start();
    connect(timer, SIGNAL(timeout()), SLOT(addMoney()));
    moneyLabel = new QLabel("Баланс: ");
    list=new QListWidget();
    QHBoxLayout *main2 = new QHBoxLayout();
    QVBoxLayout *main1 = new QVBoxLayout();
    QHBoxLayout *main = new QHBoxLayout();
    QPushButton *transaction1=new QPushButton();
    transaction1->setText("Отправить деньги");
    QPushButton *exportWallet=new QPushButton();
    exportWallet->setText("Экcпорт");
    QPushButton *exit=new QPushButton();
    exit->setText("Выход");
    main2->addWidget(exportWallet);
    main2->addWidget(exit);
    main1->addWidget(moneyLabel);
    main1->addWidget(transaction1);
    main1->addLayout(main2);
    main->addLayout(main1);
    main->addWidget(list);
    setLayout(main);
    if(_access_s("encryptionKeyLong.txt",0))
    encryptionKey();
    if(_access_s("moneyHistory.txt",0))
    {
     std::ofstream moneyHistory ("moneyHistory.txt ");
      money = "0";
      moneyHistory<<encryption(money);
      moneyHistory.close();
    }
    else
    {
        std::string temp;
        std::ifstream moneyHistory ("moneyHistory.txt ");
        std::getline(moneyHistory, money);
        moneyLabel->setText("Баланс: " + QString::fromStdString(decryption(money)));
        while(!moneyHistory.eof())
        {
            std::getline(moneyHistory, temp);
            list->addItem(QString::fromStdString(decryption(temp)));
        }
    }
    connect(exit,SIGNAL(clicked()), this, SLOT(close()));
    connect(transaction1,SIGNAL(clicked()), this, SLOT(transactionSlot()));
    connect(exportWallet,SIGNAL(clicked()), this, SLOT(exportSlot()));
}
void WalletWindow::transactionSlot()
{
    transaction *window2=new transaction(money, IDString);
    connect(window2,SIGNAL(moneySignal(std::string)), SLOT(moneySlot(std::string)));
    connect(window2, SIGNAL(transactionSignal(QString)), SLOT(stringSlot(QString)));
    window2->show();
}
void WalletWindow::exportSlot()
{
std::string temp;
std::ofstream exportWallet("exportWallet.txt");
std::ifstream enKey("encryptionKey.txt");
std::getline(enKey,temp);
exportWallet<<temp;
exportWallet<<std::endl;
enKey.close();
std::ifstream enKeyL("encryptionKeyLong.txt");
std::getline(enKeyL,temp);
exportWallet<<temp;
exportWallet<<std::endl;
enKeyL.close();
std::ifstream wallet("wallet.txt");
while(!wallet.eof())
{
 std::getline(wallet,temp);
 exportWallet<<temp<<std::endl;
}
wallet.close();
std::ifstream money("moneyHistory.txt");
while(!money.eof())
{
 std::getline(money,temp);
 exportWallet<<temp<<std::endl;
}
money.close();
exportWallet.close();
}
void WalletWindow::stringSlot(QString a)
{
    list->addItem(a);
    rewriteHistory();
}

void WalletWindow:: moneySlot(std::string money1)
{

    long int tmoney = strToInt(money)-strToInt(money1);
    std::stringstream moneystream;
    moneystream<<tmoney;
    money = moneystream.str();
    moneyLabel->setText("Баланс: "  + QString::fromStdString(money));
    rewriteHistory();
}
long int WalletWindow :: strToInt(std::string &money)
{
    char *buff =new char [money.length()];
    for(int i=0;i<money.length();i++)
        buff[i]=money[i];
    long int tMoney = atoi(buff);
    return tMoney;
}
void WalletWindow::addMoney()
{
    std::string str;
    for(int i=0;i<32;i++)
    str += rand() % 10 + 48;
    short int tempMoney;
    tempMoney=rand() % 999 + 1;
    long int thisMoney = strToInt(money);
    thisMoney += tempMoney;
    std::stringstream itos;
    itos << tempMoney;
    str += '\t' + itos.str();
    itos.seekp(0);
    itos << thisMoney;
    money = itos.str();
    moneyLabel->setText("Баланс: " + QString::fromStdString(money));
    list->addItem(QDateTime::currentDateTime().toString("dd.MM.yy    HH:mm:ss\t") + QString::fromStdString(str));
    rewriteHistory();
    timer->setInterval(rand() % 360000);
    timer->start();
}
 void WalletWindow::IDSlot(std::string& temp)
 {
      IDString=temp;
 }


void WalletWindow::rewriteHistory()
{
   std::ofstream infoHistory("moneyHistory.txt");
   infoHistory<<encryption(money)<<std::endl;
   for(int i=0;i < list->count(); i++){
       infoHistory<<encryption(list->item(i)->text().toStdString());
       if(i + 1 != list->count())
           infoHistory<<std::endl;
   }
   infoHistory.close();
}
void WalletWindow:: encryptionKey()
{
    char *key = new char[14];
    for(int i=0; i<15;i++)
    {
        key[i]=rand() % 65 + 25;

        for (int j=0;j<i;j++)
        if(key[j]==key[i])
                i--;
    }
    std::ofstream walletOf ("encryptionKeyLong.txt");
    for(int i=0;i<15;i++)
        walletOf<<key[i];
    walletOf.close();
}
std::string WalletWindow::encryption(std::string &temp)
{
    std::string key;
    std::string a;
    std::ifstream enKey("encryptionKeyLong.txt");
    std::getline(enKey,key);
    for(int i=0;i<(int)temp.length();i++)
    {
     if(temp[i]>='0'&&temp[i]<='9')
        a+=key[(int)temp[i]-48];
   if(temp[i]==' ')
      a+=key[10];
    if(temp[i]=='-')
       a+=key[11];
    if(temp[i]==':')
      a+=key[12];
    if(temp[i]=='.')
        a+=key[13];
    if(temp[i]=='\t')
       a+=key[14];
   }
   return a;
}
 std::string WalletWindow:: decryption(std::string &temp)
{
    std::string key;
    std::string a;
    std::ifstream enKey("encryptionKeyLong.txt");
    std::getline(enKey,key);
    for(int i=0;i<(int)temp.length();i++)
    {
     for(int k=0;k<key.length();k++)
      {
         if(temp[i]==key[k])
         {
           if(k>=0 && k<=9)
              a+=k+48;
           if(k==10)
              a+=' ';
           if(k==11)
              a+='-';
           if(k==12)
              a+=':';
           if(k==13)
              a+='.';
         if(k==14)
              a+='\t';
         }
      }
   }
    return a;
}
