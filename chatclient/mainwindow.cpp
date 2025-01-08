#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatclient.h"
#include "creategroupchat.h"
#include <QLabel>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QMessageBox>

void MainWindow::clearLayout(QLayout *layout) {
    if (!layout) return;

    // Iterate over all items in the layout
    while (QLayoutItem *item = layout->takeAt(0)) {
        // If the item is a widget, delete it
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        // If the item contains a sub-layout, recursively clear it
        if (QLayout *childLayout = item->layout()) {
            clearLayout(childLayout);
        }
        // Delete the layout item itself
        delete item;
    }
}

void MainWindow::addLeftMessage(const QString& name, const QString& message) {
    QHBoxLayout* leftMessageLayout = new QHBoxLayout();

    QVBoxLayout* nameMessageLayout = new QVBoxLayout();

    QLabel* usernameLabel = new QLabel(name);
    usernameLabel->setStyleSheet("color: #4C5F50; font-weight: bold;");
    usernameLabel->setWordWrap(true);
    usernameLabel->setFixedHeight(20);
    nameMessageLayout->addWidget(usernameLabel);

    QLabel* leftMessage = new QLabel(message);
    leftMessage->setStyleSheet("background-color: #FFFFFF; border-radius: 10px; padding: 8px");
    leftMessage->setWordWrap(true);
    leftMessage->setFixedHeight(40);
    nameMessageLayout->addWidget(leftMessage);

    leftMessageLayout->addLayout(nameMessageLayout);
    leftMessageLayout->addStretch(); // Push to the left
    ui->chatLayout->addLayout(leftMessageLayout);
}

void MainWindow::addRightMessage(const QString &message) {
    QHBoxLayout* rightMessageLayout = new QHBoxLayout();
    QLabel* rightMessage = new QLabel(message);
    rightMessage->setStyleSheet("background-color: #DCF8C6; border-radius: 10px; padding: 8px;");
    rightMessage->setWordWrap(true);
    rightMessage->setFixedHeight(40);
    rightMessageLayout->addStretch(); // Push to the right
    rightMessageLayout->addWidget(rightMessage);
    ui->chatLayout->addLayout(rightMessageLayout);
}

void MainWindow::addNotification(const QString &message) {
    QHBoxLayout* leftMessageLayout = new QHBoxLayout();
    QLabel* leftMessage = new QLabel(message);
    leftMessage->setWordWrap(true);
    leftMessage->setFixedHeight(40);
    leftMessageLayout->addWidget(leftMessage);
    leftMessageLayout->addStretch(); // Push to the left
    ui->chatLayout->addLayout(leftMessageLayout);
}

void MainWindow::setUsername(const QString &name) {
    this->chatClient->setName(name);
}

void MainWindow::onJoinRoomClicked() {
    clearLayout(ui->chatLayout);
    QString roomName = ui->chatRoomsList->currentItem()->text();
    if (!roomName.isEmpty()) {
        chatClient->joinRoom(roomName);
        ui->statusBar->showMessage("Joined room: " + roomName);
    }
}

void MainWindow::onRequestChat11() {
    QString chatPartner = ui->onlineUsersList->currentItem()->text();
    if (!chatPartner.isEmpty()) {
        chatClient->requestChat11(chatPartner);
    }
}

void MainWindow::onSendMessageClicked() {
    QString message = ui->messageEdit->text().trimmed();
    if (!message.isEmpty()) {
        addRightMessage(message);
        if (!chatClient->getCurrentRoom().isEmpty())
            chatClient->sendMessageToRoom(message, chatClient->getCurrentRoom());
        else chatClient->sendPrivateMessage(message, chatClient->getChatPartner());
        ui->messageEdit->clear();

        ui->chatLayout->parentWidget()->adjustSize();
        QApplication::processEvents();
        QScrollBar *scrollBar = ui->scrollArea->verticalScrollBar();
        scrollBar->setValue(scrollBar->maximum());
    }
}

void MainWindow::onMessageReceived(const QString &roomName, const QString &username, const QString &message) {
    QString user = chatClient->getName();
//    if (roomName == chatClient->getCurrentRoom()) {
//        qDebug() << "Reveived message: " << message;
        QStringList parts = message.split(": ", Qt::SkipEmptyParts);
        if (parts.size() == 2) {
            if (parts[0] == user) addRightMessage(parts[1]);
            else
            addLeftMessage(parts[0], parts[1]);
        } else {
            addNotification(message);
        }
        ui->chatLayout->parentWidget()->adjustSize();
        QApplication::processEvents();
        QScrollBar *scrollBar = ui->scrollArea->verticalScrollBar();
        scrollBar->setValue(scrollBar->maximum());
//    }
}

void MainWindow::addInviteNotification(const QString& sender, const QString& roomName) {
    QLabel* inviteLabel = new QLabel(sender + " has invited you to " + roomName);
    QPushButton* acceptButton = new QPushButton("Accept");
    QPushButton* declineButton = new QPushButton("Decline");

    connect(acceptButton, &QPushButton::clicked, this, [this, roomName]() {
        chatClient->joinChatRoom(roomName);
    });

    connect(declineButton, &QPushButton::clicked, this, [this, sender]() {
        chatClient->declineInvite(sender);
    });

    QHBoxLayout* inviteLayout = new QHBoxLayout();
    inviteLayout->addWidget(inviteLabel);
    inviteLayout->addWidget(acceptButton);
    inviteLayout->addWidget(declineButton);

    ui->notificationsLayout->addLayout(inviteLayout);
}

void MainWindow::onCreateRoom() {
    createGroupChat = new class creategroupchat(chatClient, this);

    connect(createGroupChat, &creategroupchat::sendDataBack, this, [&](const QString &data) {
        chatClient->createRoom(data);
        ui->statusBar->showMessage("Room created: " + data);
    });
    createGroupChat->show();
}

void MainWindow::onInviteToRoom() {
    if (!chatClient->getCurrentRoom().isEmpty())
    {
        inviteToRoom = new class InviteToRoom(chatClient, this);

        connect(inviteToRoom, &InviteToRoom::sendDataBack, this, [&](const QString &targetName) {
            QString roomName =chatClient->getCurrentRoom();
            chatClient->inviteUserToRoom(targetName, roomName);
        });
        inviteToRoom->show();
    }
}

void MainWindow::onRemoveRoomUser() {
    if (!chatClient->getCurrentRoom().isEmpty()) {
        removeRoomUser = new class RemoveRoomUser(chatClient, this);
        removeRoomUser->show();
    }
}

void MainWindow::onFriendRequest() {
    friendrequest = new class friendRequest(chatClient, this);
    friendrequest->show();
}

void MainWindow::onFriendListRequest() {
    friendsList = new class FriendsList(chatClient, this);
    friendsList->show();
}

MainWindow::MainWindow(ChatClient *client, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , chatClient(client) // Khởi tạo biến client
{
    ui->setupUi(this);
    ui->userName->setText(chatClient->getName());
//    chatClient->requestOnlineFriends();
//    chatClient->requestUserRooms();
    ui->scrollAreaWidgetContents->setLayout(ui->chatLayout);

    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onSendMessageClicked);
    connect(ui->createRoomButton, &QPushButton::clicked, this, &MainWindow::onCreateRoom);
    connect(ui->inviteToRoomButton, &QPushButton::clicked, this, &MainWindow::onInviteToRoom);
    connect(ui->removeRoomUserButton, &QPushButton::clicked, this, &MainWindow::onRemoveRoomUser);
    connect(ui->friendRequestButton, &QPushButton::clicked, this, &MainWindow::onFriendRequest);
    connect(ui->friendListButton, &QPushButton::clicked, this, &MainWindow::onFriendListRequest);

    connect(ui->joinRoomButton, &QPushButton::clicked, this, &MainWindow::onJoinRoomClicked);
    connect(ui->requestChat11, &QPushButton::clicked, this, &MainWindow::onRequestChat11);
    connect(client, &ChatClient::messageReceived, this, &MainWindow::onMessageReceived);
    connect(chatClient, &ChatClient::actionSuccess, this, &MainWindow::onActionSuccess);
    connect(chatClient, &ChatClient::actionFailed, this, &MainWindow::onActionFailed);

    connect(chatClient, &ChatClient::onlineFriendsReceived, this, [this](const QStringList& users) {
        ui->onlineUsersList->clear();
        if (!users.isEmpty()) {
            for (const QString& user : users) {
                ui->onlineUsersList->addItem(user);
            }
        }
    });
    connect(ui->reloadButton, &QPushButton::clicked, this, [this] {
        chatClient->requestOnlineFriends();
    });
    connect(ui->reloadButton_2, &QPushButton::clicked, this, [this] {
        chatClient->requestUserRooms();
    });

    connect(chatClient, &ChatClient::userRoomsReceived, this, [this](const QStringList& rooms) {
        ui->chatRoomsList->clear();
        for (const QString& room : rooms) {
            ui->chatRoomsList->addItem(room);
        }
    });

    connect(chatClient, &ChatClient::inviteRoomReceived, this, [this](const QString& senderName, const QString& roomName) {
        // Hiển thị thông báo mời
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Invitation", senderName + " has invited you to join room: " + roomName,
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            chatClient->joinChatRoom((roomName));
        } else {
            chatClient->declineInvite((senderName));
        }
    });


    connect(chatClient, &ChatClient::inviteChat11Received, this, [this](const QString& senderName) {
        // Hiển thị thông báo mời
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Invitation", senderName + " has invited you to chat ",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            ui->statusBar->showMessage("Chat Private " + senderName);
            chatClient->acceptChatRequest(senderName);
            chatClient->joinPrivateChat(senderName);
        } else {
            chatClient->declineInvite((senderName));
        }
    });

    connect(ui->leaveRoomButton, &QPushButton::clicked, this, [this]() {
        if (!chatClient->getCurrentRoom().isEmpty()) {
            QString roomName = chatClient->getCurrentRoom();
            chatClient->leaveChatRoom(roomName);
            ui->statusBar->showMessage("You left the room: " + roomName);
            clearLayout(ui->chatLayout);
        } else {
            chatClient->disconnectChat11(chatClient->getChatPartner());
            clearLayout(ui->chatLayout);
        }

    });

    connect(chatClient, &ChatClient::beRemovedFromRoom, this, [this]() {
        chatClient->setCurrentRoom("");
        clearLayout(ui->chatLayout);
    });

    connect(chatClient, &ChatClient::clearChat, this, [this]() {
        clearLayout(ui->chatLayout);
        ui->statusBar->showMessage("");
    });

}

void MainWindow::onActionSuccess(const QString& message) {
    if(message.contains("has accepted your request")) ui->statusBar->showMessage("Private chat");
    QMessageBox::information(this, "Successful", message);
}

void MainWindow::onActionFailed(const QString &message) {
    QMessageBox::warning(this, "Failed", message);
}

MainWindow::~MainWindow() {
    delete ui;
}



