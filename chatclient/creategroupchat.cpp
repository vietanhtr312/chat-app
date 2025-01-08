#include "creategroupchat.h"
#include "ui_creategroupchat.h"

creategroupchat::creategroupchat(ChatClient *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creategroupchat),
    chatClient(client)
{
    ui->setupUi(this);
    chatClient->requestOnlineFriends();

    connect(chatClient, &ChatClient::onlineFriendsReceived, this, [this](const QStringList& users) {
        ui->listWidget->clear();
        for (const QString& user : users) {
            ui->listWidget->addItem(user);
        }
    });

    connect(ui->createRoomButton, &QPushButton::clicked, this, &creategroupchat::onCreateRoomClicked);
}

creategroupchat::~creategroupchat()
{
    delete ui;
}

void creategroupchat::onCreateRoomClicked() {
    QString roomName = ui->roomNameInput->text();
    if (!roomName.isEmpty()) {
//        qDebug() << "Roomname: " << roomName;
        emit sendDataBack(roomName);
        this->close();
    }
}

