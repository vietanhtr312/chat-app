#ifndef CHAT11_H
#define CHAT11_H

#include "user.h"
#include "utils.h"

void generate_fixed_id(char *buffer);
void ensure_directory_exists(const char *path);
char *get_or_create_shared_conversation_id(const char *sender_file, const char *receiver_file, char *buffer);
void request_private_message(client_t *user_list, client_t *sender, client_t *receiver);
void accept_chat_request(client_t *sender, client_t *receiver);
void decline_chat_request(client_t *sender, client_t *receiver);
void disconnect_chat(client_t *sender, client_t *receiver);
void send_private_message(client_t *sender, client_t *receiver, const char *message);
void store_message(char *senderName, char *receiverName, const char *message);
void retrieve_message(int sockfd, char *senderName, char *receiverName);

#endif // CHAT11_H