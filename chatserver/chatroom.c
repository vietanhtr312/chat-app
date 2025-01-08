#include "chatroom.h"

pthread_mutex_t chatroom_mutex = PTHREAD_MUTEX_INITIALIZER;

chatroom_t* create_chatroom(const char* room_name) {
    chatroom_t* room = (chatroom_t* ) malloc(sizeof(chatroom_t));
    strcpy(room->room_name, room_name);
    room->member_count = 0;
    room->next = NULL;
    return room;
}

int is_admin(chatroom_t* room, client_t* client) {
    return (strcmp(room->admin->name, client->name) == 0);
}

void add_chatroom(chatroom_t** head, const char* room_name, client_t* client) {
    pthread_mutex_lock( &chatroom_mutex);
    chatroom_t* new_room = create_chatroom(room_name);
    new_room->members[new_room->member_count++] = client;
    new_room->admin = client;
    new_room->next =* head;
   * head = new_room;
    pthread_mutex_unlock( &chatroom_mutex);
}

chatroom_t* find_chatroom(chatroom_t* head, const char* room_name) {
    chatroom_t* current = head;
    while (current) {
        if (strcmp(current->room_name, room_name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void add_member_to_chatroom(chatroom_t* room, client_t* client) {
    pthread_mutex_lock( &chatroom_mutex);
    if (room->member_count < MAX_CLIENTS) {
        room->members[room->member_count++] = client;
    }
    pthread_mutex_unlock( &chatroom_mutex);
}

void send_message_to_chatroom(chatroom_t* room, char* message, int sender_uid) {
    pthread_mutex_lock( &chatroom_mutex);
    for (int i = 0; i < room->member_count; i++) {
        if (room->members[i]->uid != sender_uid) {
            send(room->members[i]->sockfd, message, strlen(message), 0);
        }
    }
    pthread_mutex_unlock( &chatroom_mutex);
}

void handle_create_room(chatroom_t** chatroom_list, Packet* packet, client_t* cli) {
    if (find_chatroom(* chatroom_list, packet->room_name) != NULL) {
        strcpy(packet->message, "Room already exists.\n");
        packet->status = 0;
    } else {
        add_chatroom(chatroom_list, packet->room_name, cli);
        strcpy(packet->message, "Room created successfully.\n");
        packet->status = 1;
    }
    send(cli->sockfd, packet, sizeof(Packet), 0);
    printf("%s\n", packet->message);
}

void handle_join_room(chatroom_t** chatroom_list, Packet* packet, client_t* cli) {
    if (find_chatroom(* chatroom_list, packet->room_name) == NULL) {
        strcpy(packet->message, "Room not exists.\n");
        packet->status = 0;
    } else {
        strcpy(packet->message, "Join room successfully.\n");
        packet->status = 1;
    }
    printf("%s\n", packet->message);
}

void handle_room_invitation(client_t* user_list, InvitePacket* invite, chatroom_t *room, int sockfd) {
    client_t* targetClient = findUser(user_list, invite->target_name);
    if (targetClient) {
        char *response  = room_users(room);
        char message[256];
        if (strstr(response, targetClient->name)) {
            snprintf(message, sizeof(message), "ERROR|%s has been room member\n", targetClient->name);
            send(sockfd, message, strlen(message), 0);
        } else {
        // Gửi lời mời tới client
            snprintf(message, sizeof(message), "INVITE|%s|%s\n", invite->sender_name, invite->room_name);
            send(targetClient->sockfd, message, strlen(message), 0);
            printf("Sent invitation to %s for room %s by %s\n", invite->target_name, invite->room_name, invite->sender_name);}
    } else {
        printf("User %s not found\n", invite->target_name);
    }
}

void handle_accept_invitation(chatroom_t** chatroom_list, Packet* packet, client_t* cli) {
    chatroom_t* room = find_chatroom(* chatroom_list, packet->room_name);
    if (room == NULL) {
        strcpy(packet->message, "Room does not exist.\n");
        packet->status = 0;
    } else {
        add_member_to_chatroom(room, cli);
        strcpy(packet->message, "Joined room successfully.\n");
        char message[1024];
        sprintf(message, "User %s has joined room\n", cli->name);
        send_message_to_chatroom(room, message, -1);
        packet->status = 1;
    }
    printf("%s\n", packet->message);
    send(cli->sockfd, packet, sizeof(Packet), 0);
}

// Gửi thông báo từ chối tới người mời
void handle_reject_invitation(client_t* user_list, Packet* packet, client_t* cli) {
    char message[256];
    snprintf(message, sizeof(message), "User %s has resjected your invite", cli->name);
    strcpy(packet->message, message);
    packet->status = 0;
    client_t* sender = findUser(user_list, packet->username);
    if (sender) send(sender->sockfd, packet, sizeof(Packet), 0);
}

char* room_users(chatroom_t* room) {
    char* response = (char* ) malloc(MAX_CLIENTS* 32);
    response[0] = '\0';
    if (room == NULL) {
        return response;
    } else {
        for (int i = 0; i < room->member_count; i++) {
            strcat(response, room->members[i]->name);
            if (i < room->member_count - 1) {
                strcat(response, ",");
            }
        }
    }
    return response;
};


void view_room_users(chatroom_t* room, int client_sock) {
    pthread_mutex_lock( &chatroom_mutex);

    if (room == NULL) {
        return;
    } else {
        char response[1024] = "ROOM_USERS|";
        for (int i = 0; i < room->member_count; i++) {
            strcat(response, room->members[i]->name);
            if (i < room->member_count - 1) {
                strcat(response, ",");
            }
        }
        strcat(response, "\n");
        send(client_sock, response, strlen(response), 0);
    }

    pthread_mutex_unlock( &chatroom_mutex);
}

void handle_remove_member(chatroom_t* chatroom_list, client_t* user_list, Packet* packet, client_t* cli) {
    chatroom_t* room = find_chatroom(chatroom_list, packet->room_name);
    client_t* target_client = findUser(user_list, packet->username);

    if (room &&target_client) {
        char response[1024];
        remove_member_from_chatroom(room, target_client, cli, response);
        remove_room_from_user(target_client, user_list, room->room_name);
        send_message_to_chatroom(room, response, -1);
    } else {
        const char* error_message = "Room or user not found.\n";
        printf("%s", error_message);
        send(cli->sockfd, error_message, strlen(error_message), 0);
    }
}

void remove_member_from_chatroom(chatroom_t* room, client_t* client, client_t* requester, char* response) {
    pthread_mutex_lock( &chatroom_mutex);
    char res[1024];

    if (room == NULL) {
        printf("Room does not exist.\n");
    } else if (!is_admin(room, requester)) {
        printf("Permission denied. Only admin can remove members.\n");
        strcpy(res, "ERROR|Permission denied. Only admin can remove members.\n");
        send(requester->sockfd, res, strlen(res), 0);
    } else {
        int index = -1;
        for (int i = 0; i < room->member_count; i++) {
            if (strcmp(room->members[i]->name, client->name) == 0) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            for (int i = index; i < room->member_count - 1; i++) {
                room->members[i] = room->members[i + 1];
            }
            room->member_count--;

            sprintf(response, "ROOM_UPDATE|%s|%s has been removed by admin.\n", room->room_name, client->name);
            sprintf(res, "ROOM_REMOVE|You has been removed from room %s by admin.\n", room->room_name);
            send(client->sockfd, res, strlen(res), 0);
        } else {
            printf("User not found in room %s\n", room->room_name);
            strcpy(res, "ERROR|User not found in room.\n");
            send(requester->sockfd, res, strlen(res), 0);
        }
    }

    pthread_mutex_unlock( &chatroom_mutex);
}

void handle_leave_chatroom(chatroom_t* chatroom_list, client_t *user_list, Packet* packet, client_t* cli) {
    chatroom_t* room = find_chatroom(chatroom_list, packet->room_name);
    client_t* user = findUser(user_list, cli->name);
    if (room) {
        char response[1024];
        leave_chatroom(&chatroom_list, room, cli, response);
        remove_room_from_user(user, user_list, room->room_name);
        send_message_to_chatroom(room, response, -1);
        packet->status = 1;
        strcpy(packet->message, "You have left chat room\n");
        send(cli->sockfd, packet, sizeof(Packet), 0);
    } else {
        const char* error_message = "Room not found.\n";
        packet->status = 0;
        strcpy(packet->message, error_message);
        send(cli->sockfd, packet, sizeof(Packet), 0);
    }
}

void delete_chatroom(chatroom_t** chatroom_list, chatroom_t* room) {
    chatroom_t* temp = *chatroom_list;  
    chatroom_t* prev = NULL;   

    if (temp != NULL &&(strcpy(temp->room_name, room->room_name) == 0)) {
       *chatroom_list = temp->next; 
        free(temp);        
        return;
    }

    while (temp != NULL &&(strcpy(temp->room_name, room->room_name) != 0)) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;

    prev->next = temp->next;

    free(temp);
}

void leave_chatroom(chatroom_t** chatroom_list, chatroom_t* room, client_t* client, char* response) {
    pthread_mutex_lock( &chatroom_mutex);

    if (room == NULL) {
        printf("Room does not exist.\n");
    } else {
        int index = -1;
        for (int i = 0; i < room->member_count; i++) {
            if (strcmp(room->members[i]->name, client->name) == 0) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            for (int i = index; i < room->member_count - 1; i++) {
                room->members[i] = room->members[i + 1];
            }
            room->member_count--;

            // Nếu admin rời nhóm
            if (is_admin(room, client)) {
                if (room->member_count > 0) {
                    room->admin = room->members[0];
                    printf("Admin %s left. New admin is %s\n", client->name, room->admin->name);
                } else {
                    printf("Room %s is empty. Deleting room.\n", room->room_name);
                    delete_chatroom(chatroom_list, room); // Hàm xóa phòng
                    pthread_mutex_unlock( &chatroom_mutex);
                    return;
                }
            }

            // Gửi thông báo tới nhóm
            sprintf(response, "ROOM_UPDATE|%s|%s has left the room.\n", room->room_name, client->name);
            printf("User %s left room %s\n", client->name, room->room_name);
        } else {
            printf("User not found in room %s\n", room->room_name);
        }
    }

    pthread_mutex_unlock( &chatroom_mutex);
}

void save_chatrooms_to_file(chatroom_t* chatroom_list,
    const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    pthread_mutex_lock( &chatroom_mutex);

    chatroom_t* current = chatroom_list;
    while (current != NULL) {
        fprintf(file, "%s|%s|", current->room_name, current->admin->name);
        for (int i = 0; i < current->member_count; i++) {
            fprintf(file, "%s", current->members[i]->name);
            if (i < current->member_count - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
        current = current->next;
    }

    pthread_mutex_unlock( &chatroom_mutex);
    fclose(file);
}

void load_chatrooms_from_file(chatroom_t **chatroom_list, client_t* user_list, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline character

        char *room_name = strtok(line, "|");
        char *admin_name = strtok(NULL, "|");
        char *members_str = strtok(NULL, "|");

        if (room_name && admin_name) {
            chatroom_t *new_room = create_chatroom(room_name);

            // Tạm thời gán admin
            client_t *admin = findUser(user_list, admin_name);
            new_room->admin = admin;

            // Thêm các thành viên
            char *member_name = strtok(members_str, ",");
            while (member_name) {
                client_t *member = findUser(user_list, member_name);
                add_member_to_chatroom(new_room, member);
                strncpy(member->room_names[member->room_count], room_name, sizeof(member->room_names[member->room_count]));
                member->room_count++;
                member_name = strtok(NULL, ",");
            }

            // Thêm phòng vào danh sách
            new_room->next = *chatroom_list;
            *chatroom_list = new_room;
        }
    }

    fclose(file);
}

void save_messages_to_file(chatroom_t* room) {
    char filename[100];
    snprintf(filename, sizeof(filename), "messages_room_%s.txt", room->room_name);

    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for saving messages");
        return;
    }

    for (int i = 0; i < room->message_count; i++) {
        message_t* msg = &room->messages[i];
        fprintf(file, "%ld|%s|%s\n", msg->timestamp, msg->sender, msg->content);
    }

    fclose(file);
    // printf("Messages saved for room: %s\n", room->room_name);
}

void save_all_messages(chatroom_t* chatroom_list) {
    pthread_mutex_lock( &chatroom_mutex);
    chatroom_t* current = chatroom_list;

    while (current) {
        save_messages_to_file(current);
        current = current->next;
    }

    pthread_mutex_unlock( &chatroom_mutex);
}

void load_messages_from_file(chatroom_t *room) {
    char filename[100];
    snprintf(filename, sizeof(filename), "messages_room_%s.txt", room->room_name);

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("No previous messages found for this room");
        return;
    }

    char line[2048];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Xóa ký tự newline

        char *timestamp_str = strtok(line, "|");
        char *sender = strtok(NULL, "|");
        char *content = strtok(NULL, "|");

        if (timestamp_str && sender && content) {
            message_t *msg = &room->messages[room->message_count++];
            msg->timestamp = atol(timestamp_str);
            strncpy(msg->sender, sender, sizeof(msg->sender));
            strncpy(msg->content, content, sizeof(msg->content));
        }
    }

    fclose(file);
}

void load_all_messages(chatroom_t *chatroom_list) {
    chatroom_t *current = chatroom_list;

    while (current) {
        load_messages_from_file(current);
        current = current->next;
    }
    printf("Messages loaded for all rooms\n");
}

void add_message_to_chatroom(chatroom_t* room,
    const char* sender,
        const char* content) {
    pthread_mutex_lock( &chatroom_mutex);

    if (room->message_count < MAX_MESSAGES) {
        message_t* msg = &room->messages[room->message_count++];
        strncpy(msg->sender, sender, sizeof(msg->sender));
        strncpy(msg->content, content, sizeof(msg->content));
        msg->timestamp = time(NULL);
    } else {
        printf("Message limit reached for room: %s\n", room->room_name);
    }

    save_messages_to_file(room); // Lưu ngay vào file
    pthread_mutex_unlock( &chatroom_mutex);
}

void send_old_messages(chatroom_t* room, int client_sock) {
    pthread_mutex_lock( &chatroom_mutex);

    for (int i = 0; i < room->message_count; i++) {
        message_t* msg = &room->messages[i];
        char buffer[2048];
        char timestamp[26]; // ctime_r writes 26 characters including the null-terminator
        ctime_r( &msg->timestamp, timestamp);

        // Remove the newline character from ctime's output
        timestamp[strcspn(timestamp, "\n")] = '\0';

        snprintf(buffer, sizeof(buffer), "%s\n", msg->content);
        send(client_sock, buffer, strlen(buffer), 0);
    }

    pthread_mutex_unlock( &chatroom_mutex);
}

void view_user_rooms(client_t* client) {
    char response[1024] = "ROOM_LIST|";
    for (int i = 0; i < client->room_count; i++) {
        strcat(response, client->room_names[i]);
        if (i < client->room_count - 1) {
            strcat(response, ",");
        }
    }
    strcat(response, "\n");
    send(client->sockfd, response, strlen(response), 0);
}

void save_user_rooms(client_t* client_list, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for saving user rooms");
        return;
    }

    client_t* current = client_list;
    while (current) {
        fprintf(file, "%s|", current->name);

        for (int i = 0; i < current->room_count; i++) {
            fprintf(file, "%s", current->room_names[i]);
            if (i < current->room_count - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
        current = current->next;
    }

    fclose(file);
    // printf("User rooms saved successfully to %s\n", filename);
}

void load_user_rooms(client_t* client, client_t* client_list) {
    client_t* current = client_list;
    while (current) {
        if (strcmp(current->name, client->name) == 0) {
            for (int i = 0; i < current->room_count; i++) {
                strcpy(client->room_names[i], current->room_names[i]);
                client->room_count++;
            }
        }
        current = current->next;
    }
    printf("User rooms loaded successfully\n");
}
