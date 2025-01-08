#ifndef FRIENDS_H
#define FRIENDS_H

#include "utils.h"
#include "user.h"

friend_list_t * get_friend_list_by_userid(int userid);
int add_friend(int user_id, int friend_id);
int remove_friend(int user_id, int friend_id);
void create_friend_list(int userid);
void delete_friend_list(int userid);
void save_friend_lists(const char * filename);
void load_friend_lists(const char * filename);
void view_friend_list(client_t * user_list, client_t * client, OnlineUser * onlineUsers, int onlineUserCount);
void view_friend_online(client_t * user_list, client_t * client, OnlineUser * onlineUsers, int onlineUserCount);
int send_friend_request(int sender_id, int receiver_id, int sender_sockfd, int receiver_sockfd);
int accept_friend_request(int sender_id, int receiver_id, int sender_sockfd);
int decline_friend_request(int receiver_id, int sender_id);
void view_friend_requests(client_t * user_list, client_t * client);

extern friend_list_t friend_lists[MAX_CLIENTS];
extern int friend_list_count;

#endif // FRIENDS_H