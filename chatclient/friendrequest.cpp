#include "friendrequest.h"
#include "ui_friendrequest.h"

friendRequest::friendRequest(ChatClient *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::friendRequest),
    chatClient(client)
{
    ui->setupUi(this);
    chatClient->requestOnlineUsers();
    chatClient->requestFriendRequest();

    connect(ui->pushButton_3, &QPushButton::clicked, this, [this]() {
        chatClient->requestOnlineUsers();
    });

    connect(ui->pushButton_5, &QPushButton::clicked, this, [this]() {
        chatClient->requestFriendRequest();
    });

    connect(chatClient, &ChatClient::onlineUsersReceived, this, [this](const QStringList& users) {
        ui->listWidget->clear();
        for (const QString& user : users) {
            ui->listWidget->addItem(user);
        }
    });

    connect(chatClient, &ChatClient::friendRequestsReceived, this, [this](const QStringList& users) {
        ui->listWidget_2->clear();
        for (const QString& user : users) {
            ui->listWidget_2->addItem(user);
        }
    });

    connect(ui->pushButton, &QPushButton::clicked, this, [this](){
        QListWidgetItem* selectedItem = ui->listWidget->currentItem();
            if (selectedItem) {
                QString targetName = selectedItem->text();
                if (targetName == chatClient->getName()) {} else
                chatClient->sendFriendRequest(targetName);
            }
    });

    connect(ui->pushButton_2, &QPushButton::clicked, this, [this](){
        QListWidgetItem* selectedItem = ui->listWidget_2->currentItem();
            if (selectedItem) {
                QString targetName = selectedItem->text();
                chatClient->acceptFriendRequest(targetName);
                this->close();
            }
    });

    connect(ui->pushButton_4, &QPushButton::clicked, this, [this](){
        QListWidgetItem* selectedItem = ui->listWidget_2->currentItem();
            if (selectedItem) {
                QString targetName = selectedItem->text();
                chatClient->declineFriendRequest(targetName);
                this->close();
            }
    });

    connect(ui->pushButton_6, &QPushButton::clicked, this, &friendRequest::close);
}

friendRequest::~friendRequest()
{
    delete ui;
}



