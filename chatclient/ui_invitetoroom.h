/********************************************************************************
** Form generated from reading UI file 'invitetoroom.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVITETOROOM_H
#define UI_INVITETOROOM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InviteToRoom
{
public:
    QLabel *label;
    QPushButton *refreshButton;
    QListWidget *listWidget;
    QPushButton *backButton;
    QPushButton *inviteButton;

    void setupUi(QDialog *InviteToRoom)
    {
        if (InviteToRoom->objectName().isEmpty())
            InviteToRoom->setObjectName(QString::fromUtf8("InviteToRoom"));
        InviteToRoom->resize(364, 271);
        InviteToRoom->setStyleSheet(QString::fromUtf8("QDialog {\n"
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
        label = new QLabel(InviteToRoom);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 121, 21));
        refreshButton = new QPushButton(InviteToRoom);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));
        refreshButton->setGeometry(QRect(288, 10, 51, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/refresh_icon.png"), QSize(), QIcon::Normal, QIcon::On);
        refreshButton->setIcon(icon);
        refreshButton->setIconSize(QSize(30, 30));
        listWidget = new QListWidget(InviteToRoom);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 50, 331, 151));
        backButton = new QPushButton(InviteToRoom);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(20, 210, 89, 41));
        backButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/return.png"), QSize(), QIcon::Normal, QIcon::On);
        backButton->setIcon(icon1);
        inviteButton = new QPushButton(InviteToRoom);
        inviteButton->setObjectName(QString::fromUtf8("inviteButton"));
        inviteButton->setGeometry(QRect(210, 210, 111, 41));
        inviteButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/add.png"), QSize(), QIcon::Normal, QIcon::On);
        inviteButton->setIcon(icon2);

        retranslateUi(InviteToRoom);

        QMetaObject::connectSlotsByName(InviteToRoom);
    } // setupUi

    void retranslateUi(QDialog *InviteToRoom)
    {
        InviteToRoom->setWindowTitle(QCoreApplication::translate("InviteToRoom", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("InviteToRoom", "List friend online", nullptr));
        refreshButton->setText(QString());
        backButton->setText(QCoreApplication::translate("InviteToRoom", "Back  ", nullptr));
        inviteButton->setText(QCoreApplication::translate("InviteToRoom", "Invite  ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InviteToRoom: public Ui_InviteToRoom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVITETOROOM_H
