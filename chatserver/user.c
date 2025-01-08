#include "user.h"

bool check;
int nb;

client_t* createUser(int uid, char* name, char* password, int status) {
    client_t* newUser = (client_t* ) malloc(sizeof(client_t));
    strcpy(newUser->name, name);
    strcpy(newUser->password, password);
    newUser->status = status;
    newUser->uid = uid;
    newUser->next = NULL;
    return newUser;
}

void addUser(client_t** head, int uid, char* username, char* password, int status) {
    client_t* newUser = createUser(uid, username, password, status);
    newUser->next =* head;
   * head = newUser;
}

void freeUsers(client_t* head) {
    client_t* tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int readFromFile(client_t** head, const char* fn, int next_id) {
    FILE* fp = fopen(fn, "r");
    if (fp == NULL) {
        printf("Can not open %s.\n", fn);
    }
    char buf[100];
    nb = 0;

    while ((fgets(buf, sizeof(buf), fp)) != NULL) {
        char* name,* password;
        int uid, status;
        uid = atoi(strtok(buf, " "));
        name = strtok(NULL, " ");
        password = strtok(NULL, " ");
        status = atoi(strtok(NULL, " "));
        addUser(head, uid, name, password, status);
        next_id = uid;
    };
    fclose(fp);
    return next_id;
}

void writeToFile(client_t* head, const char* fn) {
    FILE* fp = fopen(fn, "w");
    if (fp == NULL) {
        printf("Can not open %s.\n", fn);
    }
    client_t* current = head;
    while (current) {
        fprintf(fp, "%d %s %s %d\n",current->uid, current->name, current->password, current->status);
        current = current->next;
    }
    fclose(fp);
}

client_t* findUser(client_t* head, char* name) {
    check = false;
    client_t* current = head;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            check = true;
            break;
        }
        current = current->next;
    }
    if (check == false)
        return NULL;
    return current;
}

client_t* findUserById(client_t* head, int uid) {
    check = false;
    client_t* current = head;

    while (current) {
        if (current->uid == uid) {
            check = true;
            break;
        }
        current = current->next;
    }
    if (check == false)
        return NULL;
    return current;
}

void updateStatus(client_t* head, char* username) {
    client_t* current = head;

    while (current) {
        if (strcmp(current->name, username) == 0) {
            if (current->status == 1) {
                current->status = 0;
                writeToFile(head, USER_FILE);
                break;
            }
        }
        current = current->next;
    }
}

void updatePassword(client_t* head, char* username, char* newpass) {
    client_t* current = head;

    while (current) {
        if (strcmp(current->name, username) == 0) {
            strcpy(current->password, newpass);
            writeToFile(head, USER_FILE);
        }
        current = current->next;
    }
}

int checkInvalidPassword(char* password) {
    for (int i = 0; i < strlen(password); i++) {
        if (!isdigit(password[i]) && !isalpha(password[i])) {
            return 0;
        }
    }
    return 1;
}

void handle_register(client_t* user_list, Packet* packet,int next_id) {
    pthread_mutex_t user_list_mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&user_list_mutex);
    if (findUser(user_list, packet->username) != NULL) {
        strcpy(packet->message, "Username already exists.\n");
        packet->status = 0;
    } else {
        addUser(&user_list, next_id, packet->username, packet->password, 1);
        writeToFile(user_list, USER_FILE);
        packet->status = 1;
        strcpy(packet->message, "Registration successful.\n");
    }
    pthread_mutex_unlock(&user_list_mutex);
}

void handle_login(client_t* user_list, Packet* packet, client_t* client) {
    pthread_mutex_t user_list_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&user_list_mutex);

    client_t* user = findUser(user_list, packet->username);
    packet->status = 0;

    if (user == NULL) {
        strcpy(packet->message, "User not found.\n");
    } else if (strcmp(user->password, packet->password) != 0) {
        strcpy(packet->message, "Incorrect password.\n");
    } else if (user->status == 0) {
        strcpy(packet->message, "Account has been blocked\n");
    } else {
        packet->status = 1;
        strcpy(packet->message, "Login successful.\n");
        user->sockfd = client->sockfd;
        client->uid = user->uid;
    }
    pthread_mutex_unlock(&user_list_mutex);
}

int addOnlineUser(OnlineUser* onlineUsers, int onlineUserCount, int socket, const char* username) {
    if (onlineUserCount < MAX_CLIENTS) {
        strncpy(onlineUsers[onlineUserCount].username, username, sizeof(onlineUsers[onlineUserCount].username));
        onlineUsers[onlineUserCount].socket = socket;
        onlineUserCount++;
        printf("%s is now online.\n", username);
    }
    return onlineUserCount;
}

int removeOnlineUser(OnlineUser* onlineUsers, int onlineUserCount, int socket) {
    for (int i = 0; i < onlineUserCount; i++) {
        if (onlineUsers[i].socket == socket) {
            printf("%s has gone offline.\n", onlineUsers[i].username);
            for (int j = i; j < onlineUserCount - 1; j++) {
                onlineUsers[j] = onlineUsers[j + 1];
            }
            onlineUserCount--;
            break;
        }
    }
    return onlineUserCount;
}

void view_online_users(OnlineUser* onlineUsers, int onlineUserCount, client_t* client) {
    char response[1024] = "ONLINE_USERS|";
    for (int i = 0; i < onlineUserCount; i++) {
        strcat(response, onlineUsers[i].username);
        if (i < onlineUserCount - 1) {
            strcat(response, ",");
        }
    }
    strcat(response, "\n");
    send(client->sockfd, response, strlen(response), 0);
}

char* online_users(OnlineUser* onlineUsers, int onlineUserCount) {
    char* response = (char* ) malloc(MAX_CLIENTS* 32);
    response[0] = '\0';
    for (int i = 0; i < onlineUserCount; i++) {
        strcat(response, onlineUsers[i].username);
        if (i < onlineUserCount - 1) {
            strcat(response, ",");
        }
    }
    return response;
};

void add_room_to_user(client_t* client, client_t* user_list, const char* room_name, int type) {
    client_t* user = findUser(user_list, client->name);

    if (client->room_count < MAX_CHATROOM) {
        strncpy(client->room_names[client->room_count], room_name, sizeof(client->room_names[client->room_count]));
        client->room_count++;
        if (type == 1) {
            strncpy(user->room_names[user->room_count], room_name, sizeof(user->room_names[user->room_count]));
            user->room_count++;
        }
    }
}

void remove_room_from_user(client_t* client, client_t* user_list, const char* room_name) {
    int index = -1;
    printf("%s %s\n", client->room_names[0], room_name);
    for (int i = 0; i < client->room_count; i++) {
        if (strcmp(client->room_names[i], room_name) == 0) {
            index = i;
            break;}
    }
        
    if (index != -1) {
        for (int j = index; j < client->room_count - 1; j++) {
            memmove(client->room_names[j], client->room_names[j + 1], sizeof(client->room_names[j]));
        }
        client->room_count--;
    }
}