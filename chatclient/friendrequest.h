#ifndef FRIENDREQUEST_H
#define FRIENDREQUEST_H

#include "chatclient.h"
#include <QDialog>

namespace Ui {
class friendRequest;
}

class friendRequest : public QDialog
{
    Q_OBJECT

public:
    explicit friendRequest(ChatClient *client, QWidget *parent = nullptr);
    ~friendRequest();

signals:
    void sendDataBack(const QString& targetName);

private slots:

private:
    Ui::friendRequest *ui;
    ChatClient *chatClient;
};

#endif // FRIENDREQUEST_H
