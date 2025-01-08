#include "signup.h"
#include "ui_signup.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>

signUp::signUp(ChatClient *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signUp),
    chatClient(client)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &signUp::onSignupButtonClicked);
    connect(chatClient, &ChatClient::signupSuccess, this, &signUp::onSignupSuccess);
    connect(chatClient, &ChatClient::signupFailed, this, &signUp::onSignupFailed);
}

signUp::~signUp()
{
    delete ui;
}

// Slot to handle login button click
void signUp::onSignupButtonClicked() {
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both username and password.");
        return;
    }

    chatClient->sendSignup(username, password);  // Send login request via ChatClient
}

void signUp::onSignupSuccess() {
    QMessageBox::information(this, "Signup Successful", "Welcome!");
    accept();  // Close the login dialog
}

void signUp::onSignupFailed(const QString &message) {
    QMessageBox::warning(this, "Signup Failed", message);
}
