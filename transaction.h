#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "libraries.h"
class transaction : public QWidget
{
    Q_OBJECT
public:
    explicit transaction(std::string &money,std::string &ID, QWidget *parent = nullptr);
private:
  QLineEdit *IDEdit;
  QLineEdit *amountEdit;
  QLabel *errorText;
  std::string money1;
  std::string ID2;
  bool cheekAmount();
  bool cheekID();
  long int  strToInt(std::string &money);
signals:
void moneySignal(std::string money);
void transactionSignal(QString);
public slots:
void okSlot();

};

#endif // TRANSACTION_H
