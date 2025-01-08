#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>

struct Packet {
    int command_type;     // Loại lệnh: 0: register, 1: login, 2: sendmsg, -1: error
    char username[32];
    char password[32];
    int status;
    char room_name[32];
    char message[2048];
};

struct InvitePacket {
    char sender_name[50];    // Tên người gửi lời mời
    char target_name[50];    // Tên người nhận lời mời
    char room_name[50];
};

class ChatClient : public QObject {
    Q_OBJECT
public:
    // Constructor
    explicit ChatClient(QObject* parent = nullptr);
    void connectToServer(const QString& host, int port);

    QString getName() const;
    void setName(const QString& name);
    QString getCurrentRoom() const;
    void setCurrentRoom(const QString& roomName);
    QString getChatPartner() const;
    void setChatPartner(const QString& name);

    void sendLogin(const QString &username, const QString &password);
    void sendSignup(const QString &username, const QString &password);
    void sendMessage(const QString& message);
    void createRoom(const QString &roomName);
    void joinRoom(const QString &roomName);
    void sendMessageToRoom(const QString &message, const QString &roomName);

    void requestOnlineUsers();
    void inviteUserToRoom(const QString& targetName, const QString& roomName);
    void joinChatRoom(const QString& roomName);
    void declineInvite(const QString& roomName);
    void requestRoomUsers(const QString& roomName);
    void requestUserRooms();
    void removeUserInRoom(const QString& roomName, const QString& userName);
    void leaveChatRoom(const QString& roomName);

    void requestOnlineFriends();
    void sendFriendRequest(const QString& targetName);
    void acceptFriendRequest(const QString& targetName);
    void declineFriendRequest(const QString& targetName);
    void requestFriendRequest();
    void requestFriendsList();
    void unfriendRequest(const QString& targetName);

    void joinPrivateChat(const QString& targetName);
    void requestChat11(const QString& targetName);
    void acceptChatRequest(const QString& targetName);
    void declineChatRequest(const QString& targetName);
    void disconnectChat11(const QString& targetName);
    void sendPrivateMessage(const QString &message, const QString &targetName);

signals:
    void signupSuccess();
    void signupFailed(const QString &message);
    void loginSuccess();
    void loginFailed(const QString &message);
//    void messageReceived(const QString& message);
    void messageReceived(const QString &roomName, const QString &username, const QString &message);
    void onlineUsersReceived(const QStringList& users);
    void roomUsersReceived(const QStringList& users);
    void onlineFriendsReceived(const QStringList& users);
    void friendRequestsReceived(const QStringList& users);
    void friendsListReceived(const QStringList& users);
    void userRoomsReceived(const QStringList& rooms);
    void inviteRoomReceived(const QString& senderName, const QString& roomName);
    void actionSuccess(const QString &message);
    void actionFailed(const QString &message);
    void beRemovedFromRoom();

    void inviteChat11Received(const QString& senderName);
    void disconnectChat11Received(const QString& senderName);
    void clearChat();

private slots:
    // Xử lý khi kết nối thành công tới server
    void onConnected();

    // Xử lý khi có dữ liệu từ server gửi về
    void onReadyRead();

private:
    QTcpSocket* socket; // Socket TCP cho giao tiếp với server
    QString clientName;
    QString currentRoom;
    QString chatPartner;
};

#endif // CHATCLIENT_H
