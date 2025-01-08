#include "chat11.h"

void ensure_directory_exists(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        if(mkdir(path, 0755) == -1) perror("mkdir failed");
    }
}
// Generates a fixed-length ID using a charset and checks for collisions
void generate_fixed_id(char *buffer) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char path[BUFFER_SIZE];
    int unique = 0;

    while (!unique) {
        for (size_t i = 0; i < CONVERSATION_ID_LENGTH; ++i) {
            buffer[i] = charset[rand() % (sizeof(charset) - 1)];
        }
        buffer[CONVERSATION_ID_LENGTH] = '\0';

        snprintf(path, BUFFER_SIZE, "conversation_data/%s.txt", buffer);
        FILE *file = fopen(path, "r");
        if (file) {
            fclose(file);
        } else {
            unique = 1;
        }
    }
}

// Retrieves or creates a shared conversation ID between sender and receiver
char *get_or_create_shared_conversation_id(const char *sender_file, const char *receiver_file, char *buffer) {
    FILE *file = fopen(sender_file, "r");
    if (file) {
        if (fgets(buffer, CONVERSATION_ID_LENGTH + 2, file)) {
            buffer[strcspn(buffer, "\n")] = '\0';
            fclose(file);
            return buffer;
        }
        fclose(file);
    }

    file = fopen(receiver_file, "r");
    if (file) {
        if (fgets(buffer, CONVERSATION_ID_LENGTH + 2, file)) {
            buffer[strcspn(buffer, "\n")] = '\0';
            fclose(file);

            file = fopen(sender_file, "w");
            if (file) {
                fprintf(file, "%s\n", buffer);
                fclose(file);
            }
            return buffer;
        }
        fclose(file);
    }

    // If no ID exists, generate a new one
    generate_fixed_id(buffer);
    file = fopen(sender_file, "w");
    if (file) {
        fprintf(file, "%s\n", buffer);
        fclose(file);
    }
    file = fopen(receiver_file, "w");
    if (file) {
        fprintf(file, "%s\n", buffer);
        fclose(file);
    }

    return buffer;
}

// Request private message
void request_private_message(client_t *user_list, client_t *sender, client_t *receiver) {
    printf("Requesting private message from %s to %s\n", sender->name, receiver->name);
    if (findUser(user_list, sender->name)->chatting_partner_id > 0 ) {
        client_t *old_receiver = findUserById(user_list, receiver->uid);
        printf("You are already in a private chat with %s\n", old_receiver->name);
        char alert_response[BUFFER_SIZE-30];
        snprintf(alert_response, BUFFER_SIZE-30, "ERROR|You are already in a private chat with %s\n", old_receiver->name);
        send(sender->sockfd, alert_response, strlen(alert_response), 0);
        return;
    } else if (findUser(user_list, receiver->name)->chatting_partner_id > 0) {
        printf("%s is already in a private chat\n", receiver->name);
        char alert_response[BUFFER_SIZE];
        snprintf(alert_response, BUFFER_SIZE-30, "ERROR|%s is already in a private chat\n", receiver->name);
        send(sender->sockfd, alert_response, strlen(alert_response), 0);
        return;
    } else {
        char message_buffer[BUFFER_SIZE];
        snprintf(message_buffer, BUFFER_SIZE, "CHAT_REQUEST|%s\n", sender->name);
        send(receiver->sockfd, message_buffer, strlen(message_buffer), 0);
    }
}

void accept_chat_request(client_t *sender, client_t *receiver) {
    sender->chatting_partner_id = receiver->uid;
    receiver->chatting_partner_id = sender->uid;
    char message_buffer[BUFFER_SIZE];
    snprintf(message_buffer, BUFFER_SIZE, "CHAT_REQUEST_ACCEPTED|%s\n", sender->name);
    send(receiver->sockfd, message_buffer, strlen(message_buffer), 0);
}

void decline_chat_request(client_t *sender, client_t *receiver) {
    char message_buffer[BUFFER_SIZE];
    snprintf(message_buffer, BUFFER_SIZE, "ERROR|%s has declined your invite\n", sender->name);
    send(receiver->sockfd, message_buffer, strlen(message_buffer), 0);
}

void disconnect_chat(client_t *sender, client_t *receiver) {
    sender->chatting_partner_id = -1;
    receiver->chatting_partner_id = -1;
    char alert_response[BUFFER_SIZE];
    snprintf(alert_response, BUFFER_SIZE, "DISCONNECT|%s has disconnected from the chat\n", sender->name);
    send(receiver->sockfd, alert_response, strlen(alert_response), 0);
    char message_buffer[BUFFER_SIZE];
    snprintf(message_buffer, BUFFER_SIZE, "%s has disconnected from the chat", sender->name);
    store_message(sender->name, receiver->name, message_buffer);
}

void send_private_message(client_t *sender, client_t *receiver, const char *message) {
    if (!message) {
        const char *response = "No message to send";
        send(sender->sockfd, response, strlen(response), 0);
        return;
    }

    send(receiver->sockfd, message, strlen(message), 0);
    log_message("User %s sent private message to %s", sender->name, receiver->name);
    // Store the message
    store_message(sender->name, receiver->name, message);
}

void store_message(char *senderName, char *receiverName, const char *message) {
    char sender_folder[BUFFER_SIZE-32], receiver_folder[BUFFER_SIZE-32];
    char sender_conversation_file[BUFFER_SIZE], receiver_conversation_file[BUFFER_SIZE];
    char conversation_folder[BUFFER_SIZE-50] = "conversation_data";
    char conversation_file[BUFFER_SIZE], conversation_id[CONVERSATION_ID_LENGTH + 1] = {0};

    // Đảm bảo thư mục tồn tại
    snprintf(sender_folder, (BUFFER_SIZE-32), "user_messages/%s", senderName);
    snprintf(receiver_folder, (BUFFER_SIZE-32), "user_messages/%s",receiverName);
    ensure_directory_exists(sender_folder);
    ensure_directory_exists(receiver_folder);

    // Tạo tệp tin cuộc trò chuyện
    snprintf(sender_conversation_file, BUFFER_SIZE, "%s/%s.txt", sender_folder, receiverName);
    snprintf(receiver_conversation_file, BUFFER_SIZE, "%s/%s.txt", receiver_folder, senderName);

    get_or_create_shared_conversation_id(sender_conversation_file, receiver_conversation_file, conversation_id);
    ensure_directory_exists(conversation_folder);

    snprintf(conversation_file, BUFFER_SIZE, "%s/%s.txt", conversation_folder, conversation_id);

    // Lưu tin nhắn vào file
    FILE *file = fopen(conversation_file, "a");
    if (file) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);
        fprintf(file, "[%s] %s\n", timestamp, message);
        fclose(file);
    }
}
// Retrieves messages from the conversation file
void retrieve_message(int sockfd, char *senderName, char *receiverName) {
    char sender_conversation_file[BUFFER_SIZE];
    char conversation_id[CONVERSATION_ID_LENGTH + 1] = {0};
    MessageList *message_list = malloc(sizeof(MessageList));
    message_list->count = 0;

    char line[BUFFER_SIZE];
    char *response_content = malloc(RESPONSE_SIZE);
    size_t response_size = 0;

    snprintf(sender_conversation_file, BUFFER_SIZE, "user_messages/%s/%s.txt",
             senderName, receiverName);

    FILE *file = fopen(sender_conversation_file, "r");
    if (file == NULL) {
        free(response_content);
        free(message_list);
        return;
    }

    if (fgets(conversation_id, CONVERSATION_ID_LENGTH + 2, file)) {
        conversation_id[strcspn(conversation_id, "\n")] = '\0';
    }
    fclose(file);

    char conversation_file[BUFFER_SIZE];
    snprintf(conversation_file, BUFFER_SIZE, "conversation_data/%s.txt", conversation_id);

    file = fopen(conversation_file, "r");
    if (file == NULL) {
        free(response_content);
        free(message_list);
        return;
    }

    while (fgets(line, sizeof(line), file) && message_list->count < MAX_11_MESSAGES) {
        Message *msg = &message_list->messages[message_list->count++];
        if (sscanf(line, "[%19[^]]] %[^:]: %[^\n]", msg->timestamp, msg->username, msg->message) == 3) {
            // Valid line parsed
        } else {
            --message_list->count; // Revert count if line is invalid
        }
    }
    fclose(file);

    for (int i = 0; i < message_list->count; i++) {
        Message *msg = &message_list->messages[i];
        int written = snprintf(response_content, sizeof(response_content), "%s: %s\n", msg->username, msg->message);
        if (written < 0 || written >= RESPONSE_SIZE - response_size) {
            break;
        }
        strcat(response_content, "\n");
        send(sockfd, response_content, strlen(response_content), 0);
    }

    char *final_response = malloc(RESPONSE_SIZE);
    if (!final_response) {
        free(response_content);
        free(message_list);
        perror("Failed to allocate memory for final response");
        return;
    }


    free(response_content);
    free(final_response);
    free(message_list);
}


