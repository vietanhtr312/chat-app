/********************************************************************************
** Form generated from reading UI file 'friendrequest.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDREQUEST_H
#define UI_FRIENDREQUEST_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_friendRequest
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QPushButton *pushButton_3;
    QListWidget *listWidget;
    QListWidget *listWidget_2;
    QLabel *label_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;

    void setupUi(QDialog *friendRequest)
    {
        if (friendRequest->objectName().isEmpty())
            friendRequest->setObjectName(QString::fromUtf8("friendRequest"));
        friendRequest->resize(514, 468);
        friendRequest->setStyleSheet(QString::fromUtf8("QDialog {\n"
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
        pushButton = new QPushButton(friendRequest);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(350, 110, 151, 51));
        pushButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/request-send.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(24, 24));
        pushButton_2 = new QPushButton(friendRequest);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(350, 280, 131, 41));
        pushButton_2->setLayoutDirection(Qt::RightToLeft);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/accept.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_2->setIcon(icon1);
        pushButton_2->setIconSize(QSize(24, 24));
        label = new QLabel(friendRequest);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 111, 17));
        pushButton_3 = new QPushButton(friendRequest);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(278, 20, 41, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/refresh_icon.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_3->setIcon(icon2);
        pushButton_3->setIconSize(QSize(30, 30));
        listWidget = new QListWidget(friendRequest);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(20, 60, 311, 141));
        listWidget_2 = new QListWidget(friendRequest);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
        listWidget_2->setGeometry(QRect(20, 250, 311, 141));
        label_2 = new QLabel(friendRequest);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 220, 111, 17));
        pushButton_4 = new QPushButton(friendRequest);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(350, 340, 131, 41));
        pushButton_4->setLayoutDirection(Qt::RightToLeft);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/decline.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_4->setIcon(icon3);
        pushButton_4->setIconSize(QSize(30, 30));
        pushButton_5 = new QPushButton(friendRequest);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(278, 210, 41, 31));
        pushButton_5->setIcon(icon2);
        pushButton_5->setIconSize(QSize(30, 30));
        pushButton_6 = new QPushButton(friendRequest);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(180, 410, 111, 41));
        pushButton_6->setLayoutDirection(Qt::RightToLeft);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix1/return.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_6->setIcon(icon4);

        retranslateUi(friendRequest);

        QMetaObject::connectSlotsByName(friendRequest);
    } // setupUi

    void retranslateUi(QDialog *friendRequest)
    {
        friendRequest->setWindowTitle(QCoreApplication::translate("friendRequest", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("friendRequest", "Send request  ", nullptr));
        pushButton_2->setText(QCoreApplication::translate("friendRequest", "Accept  ", nullptr));
        label->setText(QCoreApplication::translate("friendRequest", "Online Users", nullptr));
        pushButton_3->setText(QString());
        label_2->setText(QCoreApplication::translate("friendRequest", "List Request", nullptr));
        pushButton_4->setText(QCoreApplication::translate("friendRequest", "Decline ", nullptr));
        pushButton_5->setText(QString());
        pushButton_6->setText(QCoreApplication::translate("friendRequest", "Back  ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class friendRequest: public Ui_friendRequest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDREQUEST_H
