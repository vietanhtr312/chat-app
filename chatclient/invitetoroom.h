#ifndef INVITETOROOM_H
#define INVITETOROOM_H

#include "chatclient.h"
#include <QDialog>

namespace Ui {
class InviteToRoom;
}

class InviteToRoom : public QDialog
{
    Q_OBJECT

public:
    explicit InviteToRoom(ChatClient *client, QWidget *parent = nullptr);
    ~InviteToRoom();

signals:
    void sendDataBack(const QString& targetName);

private slots:
    void onInviteClicked();

private:
    Ui::InviteToRoom *ui;
    ChatClient *chatClient;
};

#endif // INVITETOROOM_H
