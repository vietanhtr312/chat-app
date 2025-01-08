#include "chatclient.h"
#include "string.h"


// Constructor
ChatClient::ChatClient(QObject* parent)
    : QObject(parent), socket(new QTcpSocket(this)) {

    // Kết nối các signal-slot
    connect(socket, &QTcpSocket::connected, this, &ChatClient::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, []() {
        qDebug() << "Disconnected from server.";
    });
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            [](QAbstractSocket::SocketError socketError) {
                qDebug() << "Socket error:" << socketError;
            });
}

void ChatClient::connectToServer(const QString &host, int port) {
    socket->connectToHost(host, port);
}

void ChatClient::sendLogin(const QString &username, const QString &password) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        struct Packet packet;
        packet.command_type = 1;

        strncpy(packet.username, username.toUtf8().constData(), sizeof(packet.username));
        strncpy(packet.password, password.toUtf8().constData(), sizeof(packet.password));

        socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
        socket->flush();
    } else {
        qDebug() << "Socket not connected!";
        emit loginFailed("Unable to connect to server.");
    }
}

void ChatClient::sendSignup(const QString &username, const QString &password) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        struct Packet packet;
        packet.command_type = 0;

        strncpy(packet.username, username.toUtf8().constData(), sizeof(packet.username));
        strncpy(packet.password, password.toUtf8().constData(), sizeof(packet.password));

        socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
        socket->flush();
    } else {
        qDebug() << "Socket not connected!";
        emit loginFailed("Unable to connect to server.");
    }
}

void ChatClient::setName(const QString &name) {
    clientName = name;
}

QString ChatClient::getName() const {
    return clientName;
}

QString ChatClient::getCurrentRoom() const {
    return currentRoom;
}

void ChatClient::setCurrentRoom(const QString &roomName){
    currentRoom = roomName;
}

QString ChatClient::getChatPartner() const {
    return chatPartner;
}

void ChatClient::setChatPartner(const QString &name) {
    chatPartner = name;
}

void ChatClient::createRoom(const QString &roomName) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        struct Packet packet;
        packet.command_type = 3;

        strncpy(packet.username, clientName.toUtf8().constData(), sizeof(packet.username));
        std::snprintf(packet.room_name, sizeof(packet.room_name), "%s", roomName.toUtf8().constData());

        socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
        socket->flush();
    } else {
        qDebug() << "Socket not connected!";
        emit loginFailed("Unable to connect to server.");
    }
}

void ChatClient::joinRoom(const QString &roomName) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        struct Packet packet;
        packet.command_type = 4;

        strncpy(packet.username, clientName.toUtf8().constData(), sizeof(packet.username));
        std::snprintf(packet.room_name, sizeof(packet.room_name), "%s", roomName.toUtf8().constData());

        socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
        socket->flush();
    } else {
        qDebug() << "Socket not connected!";
        emit loginFailed("Unable to connect to server.");
    }
}
void ChatClient::sendMessageToRoom(const QString &message, const QString &roomName) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        struct Packet packet;
        packet.command_type = 2;

        QString newmessage = clientName + ": " + message + "\n";

        strncpy(packet.message, newmessage.toUtf8().constData(), sizeof(packet.message));
        strncpy(packet.username, clientName.toUtf8().constData(), sizeof(packet.username));
        std::snprintf(packet.room_name, sizeof(packet.room_name), "%s", roomName.toUtf8().constData());

        socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
        socket->flush();
    } else {
        qDebug() << "Socket not connected!";
        emit actionFailed("Unable to send message.");
    }
}

void ChatClient::sendPrivateMessage(const QString &message, const QString &targetName) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        struct Packet packet;
        packet.command_type = 21;

        QString newmessage = clientName + ": " + message + "\n";
        strncpy(packet.message, newmessage.toUtf8().constData(), sizeof(packet.message));
        strncpy(packet.username, targetName.toUtf8().constData(), sizeof(packet.username));

        socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
        socket->flush();
    } else {
        qDebug() << "Socket not connected!";
        emit actionFailed("Unable to send message.");
    }
}

void ChatClient::requestOnlineUsers() {
    struct Packet packet;
    packet.command_type = 5;
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}

void ChatClient::requestRoomUsers(const QString &roomName) {
    struct Packet packet;
    packet.command_type = 8;
    strncpy(packet.room_name, roomName.toUtf8().constData(), sizeof(packet.room_name));
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}


void ChatClient::inviteUserToRoom(const QString& targetName, const QString& roomName) {
    struct Packet packet;
    packet.command_type = 6;
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));

    struct InvitePacket invite;
    strncpy(invite.target_name, targetName.toUtf8().constData(), sizeof(invite.target_name));
    strncpy(invite.room_name, roomName.toUtf8().constData(), sizeof(invite.room_name));
    strncpy(invite.sender_name, clientName.toUtf8().constData(), sizeof(invite.sender_name));
    socket->write(reinterpret_cast<const char*>(&invite), sizeof(InvitePacket));
}

void ChatClient::joinChatRoom(const QString& roomName) {
    struct Packet packet;
    packet.command_type = 7;
    packet.status = 1;
    strncpy(packet.room_name, roomName.toUtf8().constData(), sizeof(packet.room_name));
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}

void ChatClient::declineInvite(const QString &senderName) {
    struct Packet packet;
    packet.command_type = 7;
    packet.status = 0;
    strncpy(packet.username, senderName.toUtf8().constData(), sizeof(packet.username));
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}

void ChatClient::removeUserInRoom(const QString& roomName, const QString& userName) {
    struct Packet packet;
    packet.command_type = 9;
    strncpy(packet.username, userName.toUtf8().constData(), sizeof(packet.username));
    strncpy(packet.room_name, roomName.toUtf8().constData(), sizeof(packet.room_name));
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}

void ChatClient::leaveChatRoom(const QString& roomName) {
    struct Packet packet;
    packet.command_type = 10;
    strncpy(packet.room_name, roomName.toUtf8().constData(), sizeof(packet.room_name));
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}

void ChatClient::requestUserRooms() {
    struct Packet packet;
    packet.command_type = 11;
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}

void ChatClient::sendFriendRequest(const QString& targetName) {
    struct Packet packet;
    packet.command_type = 12;
    strncpy(packet.username, targetName.toUtf8().constData(), sizeof(packet.username));
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}
void ChatClient::acceptFriendRequest(const QString& targetName){
    struct Packet packet;
    packet.command_type = 13;
    packet.status = 1;
    strncpy(packet.username, targetName.toUtf8().constData(), sizeof(packet.username));
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}
void ChatClient::declineFriendRequest(const QString& targetName){
    struct Packet packet;
    packet.command_type = 13;
    packet.status = 0;
    strncpy(packet.username, targetName.toUtf8().constData(), sizeof(packet.username));
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}

void ChatClient::requestFriendRequest() {
    struct Packet packet;
    packet.command_type = 14;
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}

void ChatClient::requestFriendsList() {
    struct Packet packet;
    packet.command_type = 15;
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}

void ChatClient::unfriendRequest(const QString &targetName) {
    struct Packet packet;
    packet.command_type = 16;
    strncpy(packet.username, targetName.toUtf8().constData(), sizeof(packet.username));
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}

void ChatClient::requestOnlineFriends() {
    struct Packet packet;
    packet.command_type = 17;
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}

void ChatClient::joinPrivateChat(const QString &targetName) {
    currentRoom = "";
    chatPartner = targetName;
}

void ChatClient::requestChat11(const QString &targetName) {
    struct Packet packet;
    packet.command_type = 18;
    strncpy(packet.username, targetName.toUtf8().constData(), sizeof(packet.username));
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}

void ChatClient::acceptChatRequest(const QString &targetName) {
    struct Packet packet;
    packet.command_type = 19;
    packet.status = 1;
    strncpy(packet.username, targetName.toUtf8().constData(), sizeof(packet.username));
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}

void ChatClient::disconnectChat11(const QString &targetName) {
    struct Packet packet;
    packet.command_type = 20;
    strncpy(packet.username, targetName.toUtf8().constData(), sizeof(packet.username));
    setChatPartner("");
    socket->write(reinterpret_cast<const char*>(&packet), sizeof(Packet));
}


void ChatClient::onConnected() {
    qDebug() << "Connected to server.";
}

void ChatClient::onReadyRead() {
    while (socket->bytesAvailable() > 0) {
        if (socket->bytesAvailable() >= sizeof(Packet)) {
            Packet packet;
            socket->read(reinterpret_cast<char*>(&packet), sizeof(Packet));


            // Giải mã dữ liệu
            QString message = QString::fromUtf8(packet.message);
            QString username = QString::fromUtf8(packet.username);
            QString roomname = QString::fromUtf8(packet.room_name);

            // Hiển thị thông tin nhận được
            qDebug() << "Received message:" << message;
            switch (packet.command_type) {
                case 0:
                    if(packet.status == 0) {
                        emit(signupFailed(message));
                    } else {
                        clientName = username;
                        emit(signupSuccess());
                    }
                    break;
                case 1:
                    if(packet.status == 0) {
                        emit(loginFailed(message));
                    } else {
                        clientName = username;
                        emit(loginSuccess());
                    }
                    break;
                case 3: case 4:
                    if(packet.status == 0) emit(actionFailed(message));
                        else {
                            emit(actionSuccess(message));
                            currentRoom = roomname;}
                    break;
                case 7:
                    if(packet.status == 0) emit(actionFailed(message));
                        else {
                            emit(actionSuccess(message));
                            emit(clearChat());
                            currentRoom = roomname;}
                    break;
                }
        } else if (socket->canReadLine()) {
            QString response = socket->readLine().trimmed();

            if (response.startsWith("ONLINE_USERS|")) {
                qDebug() << response;
                QStringList parts = response.mid(13).split(',');
                emit onlineUsersReceived(parts);
            }else if (response.startsWith("ROOM_USERS|")) {
                QStringList parts = response.mid(11).split(',');
                emit roomUsersReceived(parts);
            } else if (response.startsWith("INVITE|")) {
                qDebug() << response;
                QStringList parts = response.split('|');
                if (parts.size() == 3) {
                    QString senderName = parts[1];
                    QString roomName = parts[2];
                    emit(inviteRoomReceived(senderName, roomName));
                }
            } else if (response.startsWith("CHAT_REQUEST|")) {
                QStringList parts = response.split('|');
                if (parts.size() == 2) {
                    QString senderName = parts[1];
                    emit(inviteChat11Received(senderName));
                }
            } else if (response.startsWith("CHAT_REQUEST_ACCEPTED|")) {
                qDebug() << response;
                QStringList parts = response.split('|');
                if (parts.size() == 2) {
                    QString senderName = parts[1];
                    currentRoom = "";
                    chatPartner = senderName;
                    emit(actionSuccess(senderName + " has accepted your request"));
                }
            } else if (response.startsWith("DISCONNECT|")) {
                qDebug() << response;
                QStringList parts = response.split('|');
                if (parts.size() == 2) {
                    QString message = parts[1];
                    emit(actionFailed(message));
                    emit(clearChat());
                }
            } else if (response.startsWith("ERROR|")) {
                qDebug() << response;
                QStringList parts = response.split('|');
                if (parts.size() == 2) {
                    QString message = parts[1];
                    emit(actionFailed(message));
                }
            } else if (response.startsWith("ROOM_UPDATE|")) {
                qDebug() << response;
                QStringList parts = response.split('|');
                if (parts.size() == 3) {
                    QString message = parts[2];
                   emit messageReceived(currentRoom, clientName, message);
                }
            } else if (response.startsWith("ROOM_LIST|")) {
                qDebug() << response;
                QStringList parts = response.mid(10).split(',');
                emit userRoomsReceived(parts);
            } else if (response.startsWith("FRIEND_REQUEST|")) {
                qDebug() << response;
                QStringList parts = response.mid(15).split(',');
                emit friendRequestsReceived(parts);
            } else if (response.startsWith("FRIEND_LIST|")) {
                qDebug() << response;
                QStringList parts = response.mid(12).split(',');
                emit friendsListReceived(parts);
            } else if (response.startsWith("ONLINE_FRIEND_LIST|")) {
                qDebug() << response;
                QStringList parts = response.mid(19).split(',');
                emit onlineFriendsReceived(parts);
            } else if (response.startsWith("ROOM_REMOVE|")) {
                qDebug() << response;
                QStringList parts = response.split('|');
                if (parts.size() == 2) {
                    QString message = parts[1];
                    emit actionFailed(message);
                    emit beRemovedFromRoom();
                }
            } else if (response.startsWith("NOTIFICATION|")) {
                qDebug() << response;
                QStringList message = response.split('|');
                emit(actionSuccess(message[1]));
            } else {
//                qDebug() << "Text line received from server:" << response;
                emit messageReceived(currentRoom, clientName, response);}
        } else {
                break; // Wait for more data
        }
    }
}
