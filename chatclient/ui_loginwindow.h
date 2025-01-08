/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QLineEdit *usernameInput;
    QLabel *label;
    QLineEdit *passwordInput;
    QLabel *label_2;
    QPushButton *loginButton;
    QPushButton *signupButton;
    QLabel *label_3;

    void setupUi(QDialog *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QString::fromUtf8("LoginWindow"));
        LoginWindow->resize(429, 300);
        LoginWindow->setStyleSheet(QString::fromUtf8("QDialog {\n"
"		background-color:  qlineargradient(\n"
"		spread:pad, x1:0, y1:0 x2:0, y2:0,\n"
"		stop: 0 #A3D8F4, stop:1 #E6F7FF\n"
"		);\n"
"		border: 2px solid #ffffff;\n"
"		boder-radius: 10px;\n"
"}\n"
"\n"
"QLineEdit {\n"
"		border: 2px solid #E63946;\n"
"		border-radius: 5px;\n"
"		padding: 5px;\n"
"		font-size: 14px;\n"
"		background-color: #ffffff;\n"
"		color: #333333;\n"
"}\n"
"\n"
"QLineEdit:forcus {\n"
"		border: 2px solid #457B9D;\n"
"		background-color: #F1FAEE;\n"
"}\n"
"\n"
"QPushButton{\n"
"		background-color: #2A9D8F;\n"
"		color: white;\n"
"		border: none;\n"
"		border-radius: 15px;\n"
"		padding: 10px 20px;\n"
"		font-size: 14px;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"background-color: #264653;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"background-color: #1B3B3A;\n"
"}\n"
"\n"
"QLabel{\n"
"font-size :14px;\n"
"color: #1D3557;\n"
"font-weight: bold;\n"
"}"));
        usernameInput = new QLineEdit(LoginWindow);
        usernameInput->setObjectName(QString::fromUtf8("usernameInput"));
        usernameInput->setGeometry(QRect(20, 70, 171, 31));
        label = new QLabel(LoginWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 81, 17));
        passwordInput = new QLineEdit(LoginWindow);
        passwordInput->setObjectName(QString::fromUtf8("passwordInput"));
        passwordInput->setGeometry(QRect(20, 170, 171, 31));
        label_2 = new QLabel(LoginWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 140, 81, 17));
        loginButton = new QPushButton(LoginWindow);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setGeometry(QRect(60, 240, 89, 41));
        signupButton = new QPushButton(LoginWindow);
        signupButton->setObjectName(QString::fromUtf8("signupButton"));
        signupButton->setGeometry(QRect(260, 240, 89, 41));
        label_3 = new QLabel(LoginWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 40, 201, 191));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/snowman.png")));

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QDialog *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LoginWindow", "Username", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWindow", "Password", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        signupButton->setText(QCoreApplication::translate("LoginWindow", "Sign Up", nullptr));
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
