#include "mainwindow.h"
#include "loginwindow.h"
#include "chatclient.h"
#include "creategroupchat.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ChatClient client;
    client.connectToServer("127.0.0.1", 1234);  // Replace with your server's IP and port

    LoginWindow login(&client);
    if (login.exec() == QDialog::Accepted) {
        MainWindow mainWindow(&client);  // Pass the client to MainWindow as well
        mainWindow.show();
        return a.exec();
    }

    return 0;  // Exit if login fails
}
