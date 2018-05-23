#ifndef WALLETWINDOW_H
#define WALLETWINDOW_H
#include "libraries.h"
#include <QListWidget>
#include <QTimer>
class WalletWindow : public QWidget
{
    Q_OBJECT
public:
    explicit WalletWindow(QWidget *parent = nullptr);
private:
    std ::string IDString;
   std::string money;
   QListWidget *list;
   QTimer *timer;
   QLabel *moneyLabel;
   void rewriteHistory();
   long int strToInt(std::string &money);
   void  encryptionKey();
   std::string encryption(std::string &temp);
   std::string  decryption(std::string&);
signals:

public slots:
  void transactionSlot();
  void exportSlot();
  void moneySlot(std::string);
  void addMoney();
  void IDSlot(std::string&);
  void stringSlot(QString);
};
#endif // WALLETWINDOW_H
