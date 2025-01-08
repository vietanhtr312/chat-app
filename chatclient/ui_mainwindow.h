/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *removeRoomUserButton;
    QPushButton *inviteToRoomButton;
    QPushButton *leaveRoomButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *notificationsLayout;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *chatLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *messageEdit;
    QPushButton *sendButton;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QPushButton *reloadButton;
    QListWidget *onlineUsersList;
    QPushButton *requestChat11;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QPushButton *createRoomButton;
    QPushButton *friendRequestButton;
    QPushButton *friendListButton;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QPushButton *reloadButton_2;
    QListWidget *chatRoomsList;
    QPushButton *joinRoomButton;
    QPushButton *removeRoomUserButton_2;
    QLabel *userName;
    QMenuBar *menubar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1061, 661);
        MainWindow->setStyleSheet(QString::fromUtf8("QDialog {\n"
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
"		border-radius: 5px;\n"
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
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(450, 150, 561, 41));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(190, 30, 835, 571));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 6);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(400, 5, -1, -1);
        removeRoomUserButton = new QPushButton(verticalLayoutWidget);
        removeRoomUserButton->setObjectName(QString::fromUtf8("removeRoomUserButton"));
        removeRoomUserButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/group_chat.png"), QSize(), QIcon::Normal, QIcon::On);
        removeRoomUserButton->setIcon(icon);
        removeRoomUserButton->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(removeRoomUserButton);

        inviteToRoomButton = new QPushButton(verticalLayoutWidget);
        inviteToRoomButton->setObjectName(QString::fromUtf8("inviteToRoomButton"));
        inviteToRoomButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/plus.png"), QSize(), QIcon::Normal, QIcon::On);
        inviteToRoomButton->setIcon(icon1);
        inviteToRoomButton->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(inviteToRoomButton);

        leaveRoomButton = new QPushButton(verticalLayoutWidget);
        leaveRoomButton->setObjectName(QString::fromUtf8("leaveRoomButton"));
        leaveRoomButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/leave.png"), QSize(), QIcon::Normal, QIcon::On);
        leaveRoomButton->setIcon(icon2);
        leaveRoomButton->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(leaveRoomButton);


        verticalLayout->addLayout(horizontalLayout_3);

        scrollArea = new QScrollArea(verticalLayoutWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setStyleSheet(QString::fromUtf8("QDialog {\n"
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
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 831, 465));
        verticalLayoutWidget_4 = new QWidget(scrollAreaWidgetContents);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(0, 0, 91, 41));
        notificationsLayout = new QVBoxLayout(verticalLayoutWidget_4);
        notificationsLayout->setObjectName(QString::fromUtf8("notificationsLayout"));
        notificationsLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_6 = new QWidget(scrollAreaWidgetContents);
        verticalLayoutWidget_6->setObjectName(QString::fromUtf8("verticalLayoutWidget_6"));
        verticalLayoutWidget_6->setGeometry(QRect(0, 40, 160, 80));
        chatLayout = new QVBoxLayout(verticalLayoutWidget_6);
        chatLayout->setObjectName(QString::fromUtf8("chatLayout"));
        chatLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        messageEdit = new QLineEdit(verticalLayoutWidget);
        messageEdit->setObjectName(QString::fromUtf8("messageEdit"));

        horizontalLayout->addWidget(messageEdit);

        sendButton = new QPushButton(verticalLayoutWidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/send.png"), QSize(), QIcon::Normal, QIcon::On);
        sendButton->setIcon(icon3);

        horizontalLayout->addWidget(sendButton);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(20, 170, 161, 201));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, -1, -1, -1);
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        reloadButton = new QPushButton(verticalLayoutWidget_2);
        reloadButton->setObjectName(QString::fromUtf8("reloadButton"));
        reloadButton->setMaximumSize(QSize(45, 16777215));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix1/refresh_icon.png"), QSize(), QIcon::Normal, QIcon::On);
        reloadButton->setIcon(icon4);
        reloadButton->setIconSize(QSize(16, 16));

        horizontalLayout_2->addWidget(reloadButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        onlineUsersList = new QListWidget(verticalLayoutWidget_2);
        onlineUsersList->setObjectName(QString::fromUtf8("onlineUsersList"));

        verticalLayout_2->addWidget(onlineUsersList);

        requestChat11 = new QPushButton(verticalLayoutWidget_2);
        requestChat11->setObjectName(QString::fromUtf8("requestChat11"));
        requestChat11->setLayoutDirection(Qt::RightToLeft);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/prefix1/chat.png"), QSize(), QIcon::Normal, QIcon::On);
        requestChat11->setIcon(icon5);

        verticalLayout_2->addWidget(requestChat11);

        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(20, 30, 161, 134));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        createRoomButton = new QPushButton(verticalLayoutWidget_3);
        createRoomButton->setObjectName(QString::fromUtf8("createRoomButton"));
        createRoomButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/new/prefix1/add_group.png"), QSize(), QIcon::Normal, QIcon::On);
        createRoomButton->setIcon(icon6);
        createRoomButton->setIconSize(QSize(20, 20));

        verticalLayout_3->addWidget(createRoomButton);

        friendRequestButton = new QPushButton(verticalLayoutWidget_3);
        friendRequestButton->setObjectName(QString::fromUtf8("friendRequestButton"));
        friendRequestButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/new/prefix1/add_friend_icon.png"), QSize(), QIcon::Normal, QIcon::On);
        friendRequestButton->setIcon(icon7);
        friendRequestButton->setIconSize(QSize(20, 20));
        friendRequestButton->setCheckable(false);
        friendRequestButton->setAutoRepeat(false);
        friendRequestButton->setAutoExclusive(false);
        friendRequestButton->setAutoDefault(false);

        verticalLayout_3->addWidget(friendRequestButton);

        friendListButton = new QPushButton(verticalLayoutWidget_3);
        friendListButton->setObjectName(QString::fromUtf8("friendListButton"));
        friendListButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/new/prefix1/friend_list.png"), QSize(), QIcon::Normal, QIcon::On);
        friendListButton->setIcon(icon8);
        friendListButton->setIconSize(QSize(20, 20));

        verticalLayout_3->addWidget(friendListButton);

        verticalLayoutWidget_5 = new QWidget(centralwidget);
        verticalLayoutWidget_5->setObjectName(QString::fromUtf8("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(20, 380, 161, 211));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(verticalLayoutWidget_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        reloadButton_2 = new QPushButton(verticalLayoutWidget_5);
        reloadButton_2->setObjectName(QString::fromUtf8("reloadButton_2"));
        reloadButton_2->setMaximumSize(QSize(45, 16777215));
        reloadButton_2->setAutoFillBackground(false);
        reloadButton_2->setIcon(icon4);

        horizontalLayout_5->addWidget(reloadButton_2);


        verticalLayout_4->addLayout(horizontalLayout_5);

        chatRoomsList = new QListWidget(verticalLayoutWidget_5);
        chatRoomsList->setObjectName(QString::fromUtf8("chatRoomsList"));

        verticalLayout_4->addWidget(chatRoomsList);

        joinRoomButton = new QPushButton(verticalLayoutWidget_5);
        joinRoomButton->setObjectName(QString::fromUtf8("joinRoomButton"));
        joinRoomButton->setLayoutDirection(Qt::RightToLeft);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/new/prefix1/join.png"), QSize(), QIcon::Normal, QIcon::On);
        joinRoomButton->setIcon(icon9);

        verticalLayout_4->addWidget(joinRoomButton);

        removeRoomUserButton_2 = new QPushButton(centralwidget);
        removeRoomUserButton_2->setObjectName(QString::fromUtf8("removeRoomUserButton_2"));
        removeRoomUserButton_2->setGeometry(QRect(190, 0, 171, 37));
        removeRoomUserButton_2->setLayoutDirection(Qt::LeftToRight);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/new/prefix1/user.png"), QSize(), QIcon::Normal, QIcon::On);
        removeRoomUserButton_2->setIcon(icon10);
        userName = new QLabel(centralwidget);
        userName->setObjectName(QString::fromUtf8("userName"));
        userName->setGeometry(QRect(316, 6, 41, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1061, 22));
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        removeRoomUserButton->setText(QCoreApplication::translate("MainWindow", "Members  ", nullptr));
        inviteToRoomButton->setText(QCoreApplication::translate("MainWindow", "Add  ", nullptr));
        leaveRoomButton->setText(QCoreApplication::translate("MainWindow", "Leave  ", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "Send   ", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Friend", nullptr));
        reloadButton->setText(QString());
        requestChat11->setText(QCoreApplication::translate("MainWindow", "Chat    ", nullptr));
        createRoomButton->setText(QCoreApplication::translate("MainWindow", "Create Room   ", nullptr));
        friendRequestButton->setText(QCoreApplication::translate("MainWindow", "Add Friend   ", nullptr));
        friendListButton->setText(QCoreApplication::translate("MainWindow", "Friend List   ", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "ChatRoom", nullptr));
        reloadButton_2->setText(QString());
        joinRoomButton->setText(QCoreApplication::translate("MainWindow", "Join   ", nullptr));
        removeRoomUserButton_2->setText(QCoreApplication::translate("MainWindow", "  User", nullptr));
        userName->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
