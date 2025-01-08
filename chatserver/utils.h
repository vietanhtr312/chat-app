#ifndef UTILS_H
#define UTILS_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdbool.h>
#include <ctype.h>
#include <signal.h>

#define BUFFER_SZ 2048
#define MAX_CLIENTS 100
#define MAX_CHATROOM 20
#define USER_FILE "account.txt"

#define MAX_FRIENDS 100
#define MAX_REQUESTS 100
#define MAX_CHATROOM 20
#define MAX_MESSAGES 1000

#define CONVERSATION_ID_LENGTH 12
#define MAX_MESSAGE_LENGTH 512
#define MAX_11_MESSAGES 1000
#define BUFFER_SIZE 1024
#define RESPONSE_SIZE (BUFFER_SIZE * MAX_11_MESSAGES + 1)


typedef struct client_t {
    struct sockaddr_in address;
    int sockfd;
    int uid;
    char name[32];
    char password[32];
    int status;
    char room_names[MAX_CHATROOM][50];
    int room_count; 
    int chatting_partner_id;
    struct client_t *next;
} client_t;

typedef struct {
    int socket;
    char username[50];
} OnlineUser;

typedef struct {
    char sender[50];
    char content[1024];
    time_t timestamp; 
} message_t;

typedef struct friend_list {
    int userid; 
    int friends[MAX_FRIENDS]; // Danh sách bạn bè (ID)
    int friend_count; // Số lượng bạn bè
    int add_friend_requests[MAX_REQUESTS]; // Yêu cầu kết bạn (ID)
    int request_count; // Số lượng yêu cầu kết bạn
} friend_list_t;

typedef struct chatroom_t {
    char room_name[32];
    client_t *admin;
    client_t *members[MAX_CLIENTS];
    int member_count;
    message_t messages[MAX_MESSAGES]; // Danh sách tin nhắn
    int message_count; // Số lượng tin nhắn
    struct chatroom_t *next;
} chatroom_t;


typedef struct Packet {
    int command_type;
    char username[32];
    char password[32];
    int status;
    char room_name[32];
    char message[BUFFER_SZ];
} Packet;

typedef struct {
    char username[50];
    char password[50];
} Account;

typedef struct {
    char sender_name[50]; // Tên người gửi lời mời
    char target_name[50]; // Tên người nhận lời mời
    char room_name[50]; // Tên chatroom
} InvitePacket;

typedef struct {
    char timestamp[20];
    char username[BUFFER_SIZE];
    char message[MAX_MESSAGE_LENGTH];
} Message;

typedef struct {
    Message messages[MAX_11_MESSAGES];
    int count;
} MessageList;

void log_message(const char *format, ...);


#endif // UTILS_H


