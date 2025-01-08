/********************************************************************************
** Form generated from reading UI file 'removeroomuser.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOVEROOMUSER_H
#define UI_REMOVEROOMUSER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_RemoveRoomUser
{
public:
    QLabel *label;
    QPushButton *refreshButton;
    QListWidget *listWidget;
    QPushButton *backButton;
    QPushButton *removeButton;

    void setupUi(QDialog *RemoveRoomUser)
    {
        if (RemoveRoomUser->objectName().isEmpty())
            RemoveRoomUser->setObjectName(QString::fromUtf8("RemoveRoomUser"));
        RemoveRoomUser->resize(367, 275);
        RemoveRoomUser->setStyleSheet(QString::fromUtf8("QDialog {\n"
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
        label = new QLabel(RemoveRoomUser);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 121, 21));
        refreshButton = new QPushButton(RemoveRoomUser);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));
        refreshButton->setGeometry(QRect(288, 10, 51, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/refresh_icon.png"), QSize(), QIcon::Normal, QIcon::On);
        refreshButton->setIcon(icon);
        refreshButton->setIconSize(QSize(30, 30));
        listWidget = new QListWidget(RemoveRoomUser);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 50, 331, 151));
        backButton = new QPushButton(RemoveRoomUser);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(30, 210, 89, 41));
        backButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/return.png"), QSize(), QIcon::Normal, QIcon::On);
        backButton->setIcon(icon1);
        removeButton = new QPushButton(RemoveRoomUser);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setGeometry(QRect(200, 210, 121, 41));
        removeButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/unfriend.png"), QSize(), QIcon::Normal, QIcon::On);
        removeButton->setIcon(icon2);
        removeButton->setIconSize(QSize(20, 20));

        retranslateUi(RemoveRoomUser);

        QMetaObject::connectSlotsByName(RemoveRoomUser);
    } // setupUi

    void retranslateUi(QDialog *RemoveRoomUser)
    {
        RemoveRoomUser->setWindowTitle(QCoreApplication::translate("RemoveRoomUser", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("RemoveRoomUser", "List room user", nullptr));
        refreshButton->setText(QString());
        backButton->setText(QCoreApplication::translate("RemoveRoomUser", "Back  ", nullptr));
        removeButton->setText(QCoreApplication::translate("RemoveRoomUser", "Remove  ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RemoveRoomUser: public Ui_RemoveRoomUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOVEROOMUSER_H
