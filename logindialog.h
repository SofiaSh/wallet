#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "libraries.h"
#include <QDialog>
class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = nullptr);
private:
    QLineEdit *password;
    QLabel *errorText;
std::string IDString;
std::string decryption(std::string &temp);
void closeEvent(QCloseEvent *);
bool formСlosing = false;
signals:
void IDSignal(std::string&);
void closed();
public slots:
    void passSlot();
};

#endif // LOGINDIALOG_H
