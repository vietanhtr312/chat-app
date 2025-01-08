#ifndef FRIENDSLIST_H
#define FRIENDSLIST_H

#include "chatclient.h"
#include <QDialog>

namespace Ui {
class FriendsList;
}

class FriendsList : public QDialog
{
    Q_OBJECT

public:
    explicit FriendsList(ChatClient *client, QWidget *parent = nullptr);
    ~FriendsList();

private:
    Ui::FriendsList *ui;
    ChatClient *chatClient;
};

#endif // FRIENDSLIST_H
