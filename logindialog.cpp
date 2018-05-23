#include "logindialog.h"
#include <QPushButton>
#include <fstream>
LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    std::ifstream walletout("wallet.txt");
    QLabel *ID = new QLabel();
    std::string temp;
    std::getline(walletout, temp);
    IDString=decryption(temp);
    ID->setText("ID: "+QString::fromStdString(IDString));
    walletout.close();
    QLabel *pass1 = new QLabel();
    pass1->setText("Введите пароль:");
    errorText = new QLabel();
    errorText->setText(" ");
    password = new QLineEdit();
    QVBoxLayout *main = new QVBoxLayout();
    QPushButton *ok=new QPushButton();
    ok->setText("OK");
    QPushButton *cancel=new QPushButton();
    cancel->setText("Отмена");
    QHBoxLayout *buttonBox=new QHBoxLayout();
    buttonBox->addWidget(ok);
    buttonBox->addWidget(cancel);
    main->addWidget(ID);
    main->addWidget(pass1);
    main->addWidget(password);
    main->addWidget(errorText);
    main->addLayout(buttonBox);
    setLayout(main);
    connect(ok, SIGNAL(clicked()), this, SLOT(passSlot()));
    connect(cancel,SIGNAL(clicked()), this, SLOT(close()));
}
void LoginDialog::passSlot()
{
std::string b;
std::ifstream walletout("wallet.txt");
std::getline(walletout, b);
std::getline(walletout, b);
std::string password_right=decryption(b);
walletout.close();
if(QString::fromStdString(password_right)!=password->text())
errorText->setText("Неверный пароль");
else
{
    formСlosing = true;
    this->close();
}
}

void LoginDialog::closeEvent(QCloseEvent *)
{
    if(formСlosing) emit IDSignal(IDString);
    else emit closed();
    this->close();
}

std::string LoginDialog:: decryption(std::string &temp)
{
   char  *key= new char[11];
   std::string a;
   std::ifstream enKey("encryptionKey.txt");
   enKey.getline(key,10);
   enKey.close();
   for(int i=0;i<(int)temp.length();i++)
    for(int k=0;k<10;k++)
     if(temp[i]==key[k])
      a+=k+48;
   return a;
}
