#include "utils.h"
#include "user.h"
#include "chatroom.h"
#include "friends.h"
#include "chat11.h"
#include "commandcode.h"

OnlineUser onlineUsers[MAX_CLIENTS];
static int onlineUserCount = 0;
static int next_id = 4;

static _Atomic unsigned int cli_count = 0;

client_t* clients[MAX_CLIENTS];
client_t* user_list = NULL;
chatroom_t* chatroom_list = NULL;

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

/* Add clients to queue*/
void queue_add(client_t* cl) {
    pthread_mutex_lock( &clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i)
        if (!clients[i]) {
            clients[i] = cl;
            break;
        }
    pthread_mutex_unlock( &clients_mutex);
}

/* Remove clients to queue*/
void queue_remove(char* name) {
    pthread_mutex_lock( &clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i)
        if (clients[i])
            if (strcpy(clients[i]->name, name) == 0) {
                clients[i] = NULL;
                break;
            }
    pthread_mutex_unlock( &clients_mutex);
}

/* Handle all communication with the client*/
void* handle_client(void* arg) {
    char buff_out[BUFFER_SZ];
    int leave_flag = 0;
    cli_count++;
    client_t* cli = (client_t* ) arg;
    Packet* packet = (Packet* ) malloc(sizeof(Packet));

    while (1) {
        if (recv(cli->sockfd, packet, sizeof(Packet), 0) <= 0) {
            onlineUserCount = removeOnlineUser(onlineUsers, onlineUserCount, cli->sockfd);
            save_all_messages(chatroom_list);
            save_user_rooms(user_list, "user_rooms.txt");
            
            save_chatrooms_to_file(chatroom_list, "chatrooms.txt");
            leave_flag = 1;
            break;
        } else {
            // printf("%d %s %s %s\n", packet->command_type, packet->username, packet->password, packet->room_name);
            switch (packet->command_type) {
            case CMD_SIGNIN:
                handle_register(user_list, packet, next_id);
                send(cli->sockfd, packet, sizeof(Packet), 0);
                if (packet->status == 1) {
                    next_id++;
                    strcpy(cli->name, packet->username);
                    onlineUserCount = addOnlineUser(onlineUsers, onlineUserCount, cli->sockfd, cli->name);
                    create_friend_list(cli->uid);
                }
                break;
            case CMD_LOGIN:
                char *online = online_users(onlineUsers, onlineUserCount);
                if (strstr(online, packet->username) != NULL ) {
                    packet->status = 0;
                    strcpy(packet->message, "You has logined already\n");
                } else {
                        handle_login(user_list, packet, cli);
                    }
                send(cli->sockfd, packet, sizeof(Packet), 0);

                if (packet->status == 0)
                    leave_flag = 1;
                else {
                    strcpy(cli->name, packet->username);
                    onlineUserCount = addOnlineUser(onlineUsers, onlineUserCount, cli->sockfd, cli->name);
                    load_user_rooms(cli, user_list);
                    if (!get_friend_list_by_userid(cli->uid)) 
                        create_friend_list(cli->uid);
                }
                break;
            case CMD_SEND_MESSAGE_TO_CHATROOM: {
                chatroom_t* room = find_chatroom(chatroom_list, packet->room_name);
                if (room) {
                    send_message_to_chatroom(room, packet->message, cli->uid);
                    log_message("User %s sent message to room %s", cli->name, room->room_name);
                    add_message_to_chatroom(room, cli->name, packet->message);
                } else {
                    strcpy(packet->message, "Room not found. Message not sent.\n");
                }}
                break;
            case CMD_CREATE_ROOM: {
                handle_create_room( &chatroom_list, packet, cli);
                if (packet->status == 1) {
                    add_room_to_user(cli, user_list, packet->room_name, 1);
                    view_user_rooms(cli);
                }}
                break;
            case CMD_JOIN_ROOM: {
                chatroom_t* room = find_chatroom(chatroom_list, packet->room_name);
                handle_join_room( &chatroom_list, packet, cli);
                send(cli->sockfd, packet, sizeof(Packet), 0);
                if (packet->status == 1)
                    send_old_messages(room, cli->sockfd);
                }
                break;
            case CMD_VIEW_ONLINE_USERS:
                view_online_users(onlineUsers, onlineUserCount, cli);
                break;
            case CMD_INVITE_TO_ROOM:{
                InvitePacket* invite = (InvitePacket* ) malloc(sizeof(InvitePacket));
                recv(cli->sockfd, invite, sizeof(InvitePacket), 0);
                chatroom_t* room = find_chatroom(chatroom_list, invite->room_name);
                handle_room_invitation(user_list, invite, room, cli->sockfd);
                }
                break;
            case CMD_RESPONSE_INVITATION:
                if (packet->status == 1) {
                    handle_accept_invitation( &chatroom_list, packet, cli);
                    add_room_to_user(cli, user_list, packet->room_name, 1);
                    view_user_rooms(cli);
                } else
                    handle_reject_invitation(user_list, packet, cli);
                break;
            case CMD_VIEW_ROOM_USERS:
                chatroom_t* current_room = find_chatroom(chatroom_list, packet->room_name);
                view_room_users(current_room, cli->sockfd);
                break;
            case CMD_REMOVE_MEMBER:
                handle_remove_member(chatroom_list, user_list, packet, cli);
                break;
            case CMD_LEAVE_ROOM:
                handle_leave_chatroom(chatroom_list, user_list, packet, cli);
                break;
            case CMD_VIEW_ROOMS:
                client_t *user = findUser(user_list, cli->name);
                view_user_rooms(user);
                break;
            case CMD_SEND_FRIEND_REQUEST : {
                client_t* user = findUser(user_list, packet->username);
                send_friend_request(cli->uid, user->uid,cli->sockfd, user->sockfd);
                }
                break;
            case CMD_RESPONSE_FRIEND_REQUEST: {
                client_t* user = findUser(user_list, packet->username);
                if (packet->status == 1) {
                    accept_friend_request(user->uid, cli->uid, user->sockfd);
                    save_friend_lists("friends_lists.txt");
                } else 
                    decline_friend_request(cli->uid, user->uid);
                }
                break;
            case CMD_VIEW_FRIEND_REQUEST:
                view_friend_requests(user_list, cli);
                break;
            case CMD_VIEW_FRIEND_LIST:
                view_friend_list(user_list, cli, onlineUsers, onlineUserCount);
                break;
            case CMD_UNFRIEND: {
                client_t *user = findUser(user_list, packet->username);
                if (user) {
                    remove_friend(cli->uid, user->uid);
                    // Xóa quan hệ ngược lại
                    remove_friend(user->uid, cli->uid);
                    save_friend_lists("friends_lists.txt");
                } else printf("Can not find user\n");
                }
                break;
            case CMD_VIEW_ONLINE_FRIENDS:
                view_friend_online(user_list, cli, onlineUsers, onlineUserCount);
                break;
            case CMD_SEND_PRIVATE_MESSAGE: {
                client_t *receiver = findUser(user_list, packet->username);
                send_private_message(cli, receiver, packet->message);
                }
                break;
            case CMD_REQUEST_PRIVATE_MESSAGE: {// 0x15: Request private message
                client_t *receiver = findUser(user_list, packet->username);
                request_private_message(user_list, cli, receiver);
                }
                break;
            case CMD_DISCONNECT_CHAT: { // 0x17: Disconnect chat
                client_t *sender = findUser(user_list, cli->name);
                client_t *receiver = findUser(user_list, packet->username);
                disconnect_chat(sender, receiver);
                }
                break;
            case CMD_RESPONSE_CHAT_REQUEST: { // 0x18: Accept chat request
                client_t *sender = findUser(user_list, cli->name);
                client_t *receiver = findUser(user_list, packet->username);
                if (packet->status == 1) {
                    accept_chat_request(sender, receiver);
                    retrieve_message(cli->sockfd, cli->name, receiver->name);
                    retrieve_message(receiver->sockfd, cli->name, receiver->name);
                    } 
                }
                break;
            }
        }
    }

    /* Delete client from queue and yield thread*/
    close(cli->sockfd);
    queue_remove(cli->name);
    free(cli);
    cli_count--;
    pthread_detach(pthread_self());

    return NULL;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char* ip = "127.0.0.1";
    int port = atoi(argv[1]);
    int option = 1;
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    pthread_t tid;

    /* Socket settings*/
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);

    /* Ignore pipe signals*/
    signal(SIGPIPE, SIG_IGN);

    if (setsockopt(listenfd, SOL_SOCKET, (SO_REUSEADDR), (char* ) &option, sizeof(option)) < 0) {
        perror("ERROR: setsockopt failed");
        return EXIT_FAILURE;
    }

    /* Bind*/
    if (bind(listenfd, (struct sockaddr* ) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR: Socket binding failed");
        return EXIT_FAILURE;
    }

    /* Listen*/
    if (listen(listenfd, 10) < 0) {
        perror("ERROR: Socket listening failed");
        return EXIT_FAILURE;
    }

    readFromFile( &user_list, USER_FILE, next_id);
    load_friend_lists("friends_lists.txt");
    load_chatrooms_from_file(&chatroom_list, user_list, "chatrooms.txt");
    load_all_messages(chatroom_list);

    while (1) {
        socklen_t clilen = sizeof(cli_addr);
        connfd = accept(listenfd, (struct sockaddr* ) &cli_addr, &clilen);

        /* Check if max clients is reached*/
        if ((cli_count + 1) == MAX_CLIENTS) {
            printf("Max clients reached. Rejected: ");
            // print_client_addr(cli_addr);
            printf(":%d\n", cli_addr.sin_port);
            close(connfd);
            continue;
        }

        /* Client settings*/
        client_t* cli = (client_t* ) malloc(sizeof(client_t));
        cli->address = cli_addr;
        cli->sockfd = connfd;

        /* Add client to the queue and fork thread*/
        queue_add(cli);
        pthread_create( &tid, NULL, &handle_client, (void* ) cli);

        /* Reduce CPU usage*/
        sleep(1);
    }

    return EXIT_SUCCESS;
}