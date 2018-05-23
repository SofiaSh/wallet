#include "transaction.h"
#include <sstream>
#include <string>
#include <QDateTime>
transaction::transaction(std::string &money, std::string &ID, QWidget *parent) : QWidget(parent)
{
money1=money;
ID2=ID;
QLabel *ID1=new QLabel();
ID1->setText("ID получателя:");
IDEdit= new QLineEdit();
QLabel *amount=new QLabel();
amount->setText("Сумма перевода:");
errorText = new QLabel();
errorText->setText(" ");
amountEdit=new QLineEdit();
QVBoxLayout *main = new QVBoxLayout();
QPushButton *ok=new QPushButton();
ok->setText("OK");
QPushButton *cancel=new QPushButton();
cancel->setText("Отмена");
QHBoxLayout *buttonBox=new QHBoxLayout();
buttonBox->addWidget(ok);
buttonBox->addWidget(cancel);
main->addWidget(ID1);
main->addWidget(IDEdit);
main->addWidget(amount);
main->addWidget(amountEdit);
main->addWidget(errorText);
main->addLayout(buttonBox);
setLayout(main);
connect(cancel,SIGNAL(clicked()), this, SLOT(close()));
connect(ok, SIGNAL(clicked()), this, SLOT(okSlot()));
}

void transaction::okSlot()
{
if(cheekAmount()&&cheekID())
{
emit moneySignal(amountEdit->text().toStdString());
QString a= (QDateTime::currentDateTime().toString("dd.MM.yy    HH:mm:ss\t")+ IDEdit->text() +"\t-"+ amountEdit->text());
emit transactionSignal (a);
this->close();
}
}

bool transaction::cheekID()
{
    std::string a=IDEdit->text().toStdString();
    if(ID2 == IDEdit->text().toStdString())
    {
        errorText->setText("Введите чужой ID");
        return false;
    }
    if(IDEdit->text().size()!=32)
    {
        errorText->setText("ID должен содержать 32 цифры");
        return false;
    }

    for(int i=0;i<(int)a.length();i++)
    {
     if(a[i]<'0' || a[i]>'9')
     {
         errorText->setText("ID должен состоять только из цифр");
         return false;
     }
    }
    return true;
}
bool transaction::cheekAmount()
{
     std::string b=amountEdit->text().toStdString();
    for(int i=0;i<(int)b.length();i++)
    {
     if(b[i]<'0' || b[i]>'9')
     {
         errorText->setText("Введите сумму числами");
         return false;
     }
    }

    if(strToInt(b)>strToInt(money1))
    {
        errorText->setText("Сумма перевода больше баланса");
        return false;
    }
    if(strToInt(b)<=0)
    {
        errorText->setText("Сумма перевода должна быть больше нуля");
        return false;
    }
    return true;
}

long int transaction :: strToInt(std::string &money)
{
    char *buff =new char [money.length()];
    for(int i=0;i<money.length();i++)
        buff[i]=money[i];
    long int tMoney = atoi(buff);
    return tMoney;
}
