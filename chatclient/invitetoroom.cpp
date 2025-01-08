#include "invitetoroom.h"
#include "ui_invitetoroom.h"

InviteToRoom::InviteToRoom(ChatClient *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InviteToRoom),
     chatClient(client)
{
    ui->setupUi(this);
    chatClient->requestOnlineFriends();

    connect(ui->refreshButton, &QPushButton::clicked, this, [this]() {
        chatClient->requestOnlineFriends();
    });

    connect(chatClient, &ChatClient::onlineFriendsReceived, this, [this](const QStringList& users) {
        ui->listWidget->clear();
        for (const QString& user : users) {
            ui->listWidget->addItem(user);
        }
    });

    connect(ui->inviteButton, &QPushButton::clicked, this, &InviteToRoom::onInviteClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &InviteToRoom::close);
}

InviteToRoom::~InviteToRoom()
{
    delete ui;
}

void InviteToRoom::onInviteClicked() {
    QListWidgetItem* selectedItem = ui->listWidget->currentItem();
        if (selectedItem) {
            QString targetName = selectedItem->text();
            emit sendDataBack(targetName);
        }
        this->close();
}

