#include "friendslist.h"
#include "ui_friendslist.h"

FriendsList::FriendsList(ChatClient *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendsList),
    chatClient(client)
{
    ui->setupUi(this);
    chatClient->requestFriendsList();

    connect(ui->refreshButton, &QPushButton::clicked, this, [this]() {
        chatClient->requestFriendsList();
    });

    connect(chatClient, &ChatClient::friendsListReceived, this, [this](const QStringList& users) {
        ui->listWidget->clear();
        for (const QString& user : users) {
            ui->listWidget->addItem(user);
        }
    });

    connect(ui->unfriendButton, &QPushButton::clicked, this, [this](){
        QListWidgetItem* selectedItem = ui->listWidget->currentItem();
            if (selectedItem) {
                QString targetName = selectedItem->text();
                QStringList newTargetName = targetName.split(" ");
                chatClient->unfriendRequest(newTargetName[0]);
                this->close();
            }
    });

    connect(ui->backButton, &QPushButton::clicked, this, &FriendsList::close);
}

FriendsList::~FriendsList()
{
    delete ui;
}



