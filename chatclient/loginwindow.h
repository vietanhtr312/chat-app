#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "chatclient.h"
#include "signup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow;}
QT_END_NAMESPACE

class LoginWindow : public QDialog {
    Q_OBJECT

public:
    explicit LoginWindow(ChatClient* client, QWidget *parent = nullptr);
    ~LoginWindow();

    QString getUsername() const;  // Trả về tên người dùng sau khi đăng nhập thành công
    void onSignupRequest();

private slots:
    void onLoginButtonClicked();
    void onLoginSuccess();
    void onLoginFailed(const QString &message);

private:
    Ui::LoginWindow *ui;
    QString username;
    ChatClient *chatClient;
    signUp *signup;
};

#endif // LOGINWINDOW_H
