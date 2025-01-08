#ifndef REMOVEROOMUSER_H
#define REMOVEROOMUSER_H

#include "chatclient.h"
#include <QDialog>

namespace Ui {
class RemoveRoomUser;
}

class RemoveRoomUser : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveRoomUser(ChatClient *client, QWidget *parent = nullptr);
    ~RemoveRoomUser();

private slots:
    void onRemoveUserClicked();

private:
    Ui::RemoveRoomUser *ui;
    ChatClient *chatClient;
};

#endif // REMOVEROOMUSER_H
