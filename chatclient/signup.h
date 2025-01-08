#ifndef SIGNUP_H
#define SIGNUP_H

#include "chatclient.h"
#include <QDialog>

namespace Ui {
class signUp;
}

class signUp : public QDialog
{
    Q_OBJECT

public:
    explicit signUp(ChatClient* client, QWidget *parent = nullptr);
    ~signUp();

private slots:
    void onSignupButtonClicked();
    void onSignupSuccess();
    void onSignupFailed(const QString &message);

private:
    Ui::signUp *ui;
    QString username;
    ChatClient *chatClient;
};

#endif // SIGNUP_H
