#ifndef CREATEGROUPCHAT_H
#define CREATEGROUPCHAT_H

#include "chatclient.h"
#include <QDialog>

namespace Ui {
class creategroupchat;
}

class creategroupchat : public QDialog
{
    Q_OBJECT

public:
    explicit creategroupchat(ChatClient *client, QWidget *parent = nullptr);
    ~creategroupchat();

signals:
    void sendDataBack(const QString& data);

private slots:
    void onCreateRoomClicked();

private:
    Ui::creategroupchat *ui;
    ChatClient *chatClient;
};

#endif // CREATEGROUPCHAT_H
