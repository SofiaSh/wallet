#include "firstdialog.h"
#include "logindialog.h"
#include <time.h>
#include <fstream>
#include <io.h>
FirstDialog::FirstDialog(QWidget *parent) : QDialog(parent)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    srand((int)time(NULL));
    for(int i=0;i<32;i++)
    IDString += rand() % 10 + 48;
    QLabel *ID = new QLabel();
    ID->setText("ID: " + QString::fromStdString(IDString));
    QLabel *pass1 = new QLabel();
    pass1->setText("Введите пароль:");
    QLabel *pass2 = new QLabel();
    pass2->setText("Повторите пароль:");
    errorText = new QLabel();
    errorText->setText(" ");
    password1 = new QLineEdit();
    password2 = new QLineEdit();
    QVBoxLayout *main = new QVBoxLayout();
    QPushButton *ok=new QPushButton();
    ok->setText("OK");
    QPushButton *cancel=new QPushButton();
    cancel->setText("Отмена");
    QPushButton *import=new QPushButton();
    import->setText("Импортировать");
    QHBoxLayout *buttonBox=new QHBoxLayout();
    buttonBox->addWidget(ok);
    buttonBox->addWidget(cancel);
    main->addWidget(ID);
    main->addWidget(pass1);
    main->addWidget(password1);
    main->addWidget(pass2);
    main->addWidget(password2);
    main->addWidget(errorText);
    main->addWidget(import);
    main->addLayout(buttonBox);
    setLayout(main);
    connect(ok, SIGNAL(clicked()), this, SLOT(passSlot()));
    connect(import,SIGNAL(clicked()),this, SLOT (importSlot()));
    connect(cancel,SIGNAL(clicked()), this, SLOT(close()));
}
void FirstDialog::importSlot()
{
    if(!_access("exportWallet.txt",0))
    {
    std::string temp;
    std::ifstream exportWallet("exportWallet.txt");
    std::ofstream enKey("encryptionKey.txt");
    std::getline(exportWallet,temp);
    enKey<<temp;
    enKey<<std::endl;
    temp.clear();
    enKey.close();
    std::ofstream enKeyL("encryptionKeyLong.txt");
    std::getline(exportWallet,temp);
    enKeyL<<temp;
    enKeyL<<std::endl;
    temp.clear();
    enKeyL.close();
    std::ofstream wallet("wallet.txt");
    std::getline(exportWallet,temp);
    wallet<<temp<<std::endl;
    std::getline(exportWallet,temp);
    wallet<<temp<<std::endl;
    temp.clear();
    wallet.close();
    std::ofstream money("moneyHistory.txt");
    while(!exportWallet.eof())
    {
     std::getline(exportWallet,temp);
    money<<temp<<std::endl;
    }
    money.close();
    exportWallet.close();
    this->close();
    LoginDialog *window2=new LoginDialog();
    window2->show();
}
    else errorText->setText("Файл не существует");
}

void FirstDialog::passSlot()
{
    if(cheсkPassWord())
    {
   encryptionKey();
   encryption(IDString,password1->text().toStdString());

    this->close();
    LoginDialog *window2=new LoginDialog();
    window2->show();
    }
}
 bool FirstDialog::cheсkPassWord()
 {
     if(password1->text().size()!=6)
     {
         errorText->setText("Пароль должен содержать 6 цифр");
         return false;
     }
     if(password1->text()!=password2->text())
     {
         errorText->setText("Пароли не совпадают");
         return false;
     }
     std::string b=password1->text().toStdString();
     for(int i=0;i<(int)b.length();i++)
     {
      if(b[i]<'0' || b[i]>'9')
      {
          errorText->setText("Пароль должен состоять только из цифр");
          return false;
      }
     }
     return true;
 }


void FirstDialog:: encryptionKey()
{
    char  *key= new char[10];
    for(int i=0; i<10;i++)
    {
        key[i]=rand() % 65 + 25;

        for (int j=0;j<i;j++)
        if(key[j]==key[i])
                i--;
    }
    std::ofstream walletOf ("encryptionKey.txt");
    for(int i=0;i<10;i++)
        walletOf<<key[i];
    walletOf.close();
}

void FirstDialog::encryption(std::string &temp1,std::string &temp2)
{
    char  *key= new char[10];
    std::string a;
    std::ifstream enKey("encryptionKey.txt");
    enKey.getline(key,10);
    std::ofstream walletOf ("wallet.txt");
    for(int i=0;i<(int)temp1.length();i++)
    a+=key[(int)temp1[i]-48];
    walletOf<<a;
    walletOf<<std::endl;
    a.clear();
    for(int i=0;i<(int)temp2.length();i++)
    a+=key[(int)temp2[i]-48];
    walletOf<<a;
    walletOf.close();
}

