#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chatclient.h"
#include "creategroupchat.h"
#include "invitetoroom.h"
#include "removeroomuser.h"
#include "friendrequest.h"
#include "friendslist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(ChatClient *client, QWidget *parent = nullptr);
    ~MainWindow();

    void addLeftMessage(const QString& name, const QString& message);
    void addRightMessage(const QString& message);
    void addNotification(const QString &message);
    void setUsername(const QString& name);
    void addInviteNotification(const QString& sender, const QString& roomName);
    void clearLayout(QLayout *layout);

private slots:
    void onCreateRoom();
    void onInviteToRoom();
    void onRemoveRoomUser();
    void onFriendRequest();
    void onFriendListRequest();
    void onJoinRoomClicked();
    void onRequestChat11();
    void onSendMessageClicked();
    void onMessageReceived(const QString &roomName, const QString &username, const QString &message);
    void onActionSuccess(const QString &message);
    void onActionFailed(const QString &message);

private:
    Ui::MainWindow *ui;
    ChatClient *chatClient; // Khai báo biến thành viên client
    creategroupchat *createGroupChat;
    InviteToRoom *inviteToRoom;
    RemoveRoomUser *removeRoomUser;
    friendRequest *friendrequest;
    FriendsList *friendsList;
};

#endif // MAINWINDOW_H
