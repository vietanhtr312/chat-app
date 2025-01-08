#include "removeroomuser.h"
#include "ui_removeroomuser.h"

RemoveRoomUser::RemoveRoomUser(ChatClient *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveRoomUser),
    chatClient(client)
{
    ui->setupUi(this);
    chatClient->requestRoomUsers(chatClient->getCurrentRoom());

    connect(ui->refreshButton, &QPushButton::clicked, this, [this]() {
        chatClient->requestRoomUsers(chatClient->getCurrentRoom());
    });

    connect(chatClient, &ChatClient::roomUsersReceived, this, [this](const QStringList& users) {
        ui->listWidget->clear();
        for (const QString& user : users) {
            ui->listWidget->addItem(user);
        }
    });

    connect(ui->removeButton, &QPushButton::clicked, this, &RemoveRoomUser::onRemoveUserClicked);

    connect(ui->backButton, &QPushButton::clicked, this, &RemoveRoomUser::close);
}

void RemoveRoomUser::onRemoveUserClicked() {
    QListWidgetItem* selectedItem = ui->listWidget->currentItem();
    if (selectedItem) {
        QString targetName = selectedItem->text();
        if (targetName != chatClient->getName()) {
            QString roomName =chatClient->getCurrentRoom();
            chatClient->removeUserInRoom(roomName, targetName);
        }
    }
}

RemoveRoomUser::~RemoveRoomUser()
{
    delete ui;
}
