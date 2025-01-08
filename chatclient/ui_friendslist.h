/********************************************************************************
** Form generated from reading UI file 'friendslist.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDSLIST_H
#define UI_FRIENDSLIST_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FriendsList
{
public:
    QLabel *label;
    QPushButton *refreshButton;
    QListWidget *listWidget;
    QPushButton *backButton;
    QPushButton *unfriendButton;

    void setupUi(QDialog *FriendsList)
    {
        if (FriendsList->objectName().isEmpty())
            FriendsList->setObjectName(QString::fromUtf8("FriendsList"));
        FriendsList->resize(391, 274);
        FriendsList->setStyleSheet(QString::fromUtf8("QDialog {\n"
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
        label = new QLabel(FriendsList);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 121, 21));
        refreshButton = new QPushButton(FriendsList);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));
        refreshButton->setGeometry(QRect(308, 10, 51, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/refresh_icon.png"), QSize(), QIcon::Normal, QIcon::On);
        refreshButton->setIcon(icon);
        refreshButton->setIconSize(QSize(30, 30));
        listWidget = new QListWidget(FriendsList);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(30, 50, 331, 151));
        backButton = new QPushButton(FriendsList);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(30, 220, 89, 41));
        backButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/return.png"), QSize(), QIcon::Normal, QIcon::On);
        backButton->setIcon(icon1);
        unfriendButton = new QPushButton(FriendsList);
        unfriendButton->setObjectName(QString::fromUtf8("unfriendButton"));
        unfriendButton->setGeometry(QRect(230, 220, 121, 41));
        unfriendButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/unfriend.png"), QSize(), QIcon::Normal, QIcon::On);
        unfriendButton->setIcon(icon2);
        unfriendButton->setIconSize(QSize(20, 20));

        retranslateUi(FriendsList);

        QMetaObject::connectSlotsByName(FriendsList);
    } // setupUi

    void retranslateUi(QDialog *FriendsList)
    {
        FriendsList->setWindowTitle(QCoreApplication::translate("FriendsList", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("FriendsList", "List friend", nullptr));
        refreshButton->setText(QString());
        backButton->setText(QCoreApplication::translate("FriendsList", "Back  ", nullptr));
        unfriendButton->setText(QCoreApplication::translate("FriendsList", "Unfriend  ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FriendsList: public Ui_FriendsList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDSLIST_H
