#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>

LoginWindow::LoginWindow(ChatClient *client, QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginWindow), chatClient(client) {
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginButtonClicked);
    connect(chatClient, &ChatClient::loginSuccess, this, &LoginWindow::onLoginSuccess);
    connect(chatClient, &ChatClient::loginFailed, this, &LoginWindow::onLoginFailed);
    connect(ui->signupButton, &QPushButton::clicked, this, &LoginWindow::onSignupRequest);
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::onSignupRequest() {
    signup = new class signUp(chatClient, this);
    signup->show();

    if (signup->exec() == QDialog::Accepted) {
        accept();
    }
}

// Slot to handle login button click
void LoginWindow::onLoginButtonClicked() {
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both username and password.");
        return;
    }

    chatClient->sendLogin(username, password);  // Send login request via ChatClient


}

void LoginWindow::onLoginSuccess() {
    QMessageBox::information(this, "Login Successful", "Welcome!");
    accept();  // Close the login dialog
}

void LoginWindow::onLoginFailed(const QString &message) {
    QMessageBox::warning(this, "Login Failed", message);
}

QString LoginWindow::getUsername() const {
    return username;
}
