#include <QApplication>
#include "firstdialog.h"
#include "logindialog.h"
#include "walletwindow.h"
#include "transaction.h"
int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
 // FirstDialog dialog;
  //LoginDialog dialog;
 WalletWindow dialog;
// transaction dialog;
dialog.show();
    return a.exec();
}
