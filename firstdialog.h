#ifndef FIRSTDIALOG_H
#define FIRSTDIALOG_H
#include <QString>
#include <stdlib.h>
#include <string>
#include "libraries.h"
#include <QDialog>
class FirstDialog : public QDialog
{
   Q_OBJECT
    public:
    explicit FirstDialog(QWidget *parent = nullptr);
    private:
    QLineEdit *password1;
    QLineEdit *password2;
    QLabel *errorText;
    std::string IDString;
    bool cheсkPassWord();
    void encryptionKey();
    void FirstDialog::encryption(std::string &temp1,std::string &temp2);
signals:

public slots:
    void passSlot();
    void importSlot();
};

#endif // FIRSTDIALOG_H
