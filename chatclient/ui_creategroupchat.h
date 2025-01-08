/********************************************************************************
** Form generated from reading UI file 'creategroupchat.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEGROUPCHAT_H
#define UI_CREATEGROUPCHAT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_creategroupchat
{
public:
    QListWidget *listWidget;
    QLabel *label;
    QLineEdit *roomNameInput;
    QPushButton *removeButton;
    QPushButton *createRoomButton;
    QPushButton *inviteButton;

    void setupUi(QDialog *creategroupchat)
    {
        if (creategroupchat->objectName().isEmpty())
            creategroupchat->setObjectName(QString::fromUtf8("creategroupchat"));
        creategroupchat->resize(400, 305);
        creategroupchat->setStyleSheet(QString::fromUtf8("QDialog {\n"
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
        listWidget = new QListWidget(creategroupchat);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(30, 71, 351, 171));
        label = new QLabel(creategroupchat);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 91, 31));
        roomNameInput = new QLineEdit(creategroupchat);
        roomNameInput->setObjectName(QString::fromUtf8("roomNameInput"));
        roomNameInput->setGeometry(QRect(120, 20, 131, 41));
        removeButton = new QPushButton(creategroupchat);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setGeometry(QRect(30, 250, 101, 41));
        removeButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/return.png"), QSize(), QIcon::Normal, QIcon::On);
        removeButton->setIcon(icon);
        createRoomButton = new QPushButton(creategroupchat);
        createRoomButton->setObjectName(QString::fromUtf8("createRoomButton"));
        createRoomButton->setGeometry(QRect(280, 250, 101, 41));
        createRoomButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/plus.png"), QSize(), QIcon::Normal, QIcon::On);
        createRoomButton->setIcon(icon1);
        inviteButton = new QPushButton(creategroupchat);
        inviteButton->setObjectName(QString::fromUtf8("inviteButton"));
        inviteButton->setGeometry(QRect(280, 20, 101, 41));
        inviteButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/add.png"), QSize(), QIcon::Normal, QIcon::On);
        inviteButton->setIcon(icon2);

        retranslateUi(creategroupchat);

        QMetaObject::connectSlotsByName(creategroupchat);
    } // setupUi

    void retranslateUi(QDialog *creategroupchat)
    {
        creategroupchat->setWindowTitle(QCoreApplication::translate("creategroupchat", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("creategroupchat", "Group Name:", nullptr));
        roomNameInput->setText(QString());
        removeButton->setText(QCoreApplication::translate("creategroupchat", "Back  ", nullptr));
        createRoomButton->setText(QCoreApplication::translate("creategroupchat", "Create  ", nullptr));
        inviteButton->setText(QCoreApplication::translate("creategroupchat", "Invite  ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class creategroupchat: public Ui_creategroupchat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEGROUPCHAT_H
