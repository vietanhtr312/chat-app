#include "friends.h"

friend_list_t friend_lists[MAX_CLIENTS];
int friend_list_count = 0;

friend_list_t * get_friend_list_by_userid(int userid) {
    for (int i = 0; i < friend_list_count; i++)
        if (friend_lists[i].userid == userid)
            return & friend_lists[i];

    return NULL; // Không tìm thấy
}

int add_friend(int user_id, int friend_id) {
    friend_list_t * list = get_friend_list_by_userid(user_id);
    if (!list || list->friend_count >= MAX_FRIENDS)
        return 0; // Không thể thêm

    // Kiểm tra trùng lặp
    for (int i = 0; i < list->friend_count; i++)
        if (list->friends[i] == friend_id)
            return 0; // Đã là bạn

    // Thêm bạn
    list->friends[list->friend_count++] = friend_id;

    return 1;
}

int remove_friend(int user_id, int friend_id) {
    friend_list_t * list = get_friend_list_by_userid(user_id);
    if (!list) return 0;

    for (int i = 0; i < list -> friend_count; i++) {
        if (list -> friends[i] == friend_id) {
            for (int j = i; j < list -> friend_count - 1; j++) {
                list -> friends[j] = list -> friends[j + 1];
            }
            list -> friend_count--;
            return 1;
        }
    }
    if (list->friend_count == 0) delete_friend_list(user_id);
    return 0; // Không tìm thấy bạn
}

void create_friend_list(int userid) {
    friend_list_t * list = & friend_lists[friend_list_count++];
    list->userid = userid;
    list->friend_count = 0;
    list->request_count = 0;
}

void delete_friend_list(int userid) {
    for (int i = 0; i < friend_list_count; i++)
        if (friend_lists[i].userid == userid) {
            for (int j = i; j < friend_list_count - 1; j++)
                friend_lists[j] = friend_lists[j + 1];
            friend_list_count--;
            break;
        }
}

void save_friend_lists(const char * filename) {
    FILE * file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for saving friend lists");
        return;
    }

    for (int i = 0; i < friend_list_count; i++) {
        friend_list_t * list = & friend_lists[i];
        fprintf(file, "%d|", list->userid);
        for (int j = 0; j < list->friend_count; j++) {
            fprintf(file, "%d", list->friends[j]);
            if (j < list->friend_count - 1)
                fprintf(file, ",");
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Friend lists saved to %s\n", filename);
}

void load_friend_lists(const char * filename) {
    FILE * file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file for loading friend lists");
        return;
    }

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), file)) {
        friend_list_t * list = & friend_lists[friend_list_count++];
        sscanf(buffer, "%d|", & list->userid);

        char * friends = strchr(buffer, '|') + 1;
        char * token = strtok(friends, ",");
        while (token) {
            list->friends[list->friend_count++] = atoi(token);
            token = strtok(NULL, ",");
        }
    }

    fclose(file);
    printf("Friend lists loaded from %s\n", filename);
}

void view_friend_list(client_t * user_list, client_t * client, OnlineUser * onlineUsers, int onlineUserCount) {
    friend_list_t * friend_list = get_friend_list_by_userid(client->uid);
    if (!user_list)
        return;
    else if (friend_list->friend_count == 0)
        return;

    char * response = online_users(onlineUsers, onlineUserCount);

    // Tạo buffer chứa danh sách bạn bè
    char friends[1024] = "FRIEND_LIST|";

    // Duyệt qua danh sách bạn bè và thêm vào buffer
    for (int i = 0; i < friend_list->friend_count; i++) {
        client_t * user = findUserById(user_list, friend_list->friends[i]);
        strcat(friends, user->name);
        if (strstr(response, user->name) != NULL)
            strcat(friends, "    		Online");
        else
            strcat(friends, "     		Offline");
        if (i < friend_list->friend_count - 1)
            strcat(friends, ","); // Thêm dấu phẩy giữa các tên
    }

    strcat(friends, "\n");
    send(client->sockfd, friends, strlen(friends), 0);
}

void view_friend_online(client_t * user_list, client_t * client, OnlineUser * onlineUsers, int onlineUserCount) {
    friend_list_t * friend_list = get_friend_list_by_userid(client->uid);
    if (!user_list)
        return; // Người dùng không tồn tại
    else if (friend_list->friend_count == 0)
        return; // Kiểm tra nếu không có bạn bè

    char *response = online_users(onlineUsers, onlineUserCount);

    // Tạo buffer chứa danh sách bạn bè
    char friends[1024] = "ONLINE_FRIEND_LIST|";

    int first = 1;
    // Duyệt qua danh sách bạn bè và thêm vào buffer
    for (int i = 0; i < friend_list->friend_count; i++) {
        client_t * user = findUserById(user_list, friend_list->friends[i]);
        if (strstr(response, user->name) != NULL) {
            if (!first) strcat(friends, ","); // Thêm dấu phẩy giữa các tên
            strcat(friends, user->name);
            first = 0;}
    }

    strcat(friends, "\n");
    send(client->sockfd, friends, strlen(friends), 0);
}

int send_friend_request(int sender_id, int receiver_id, int sender_sockfd, int receiver_sockfd) {
    friend_list_t * receiver_list = get_friend_list_by_userid(receiver_id);
    if (!receiver_list)
        return 0; // Người nhận không tồn tại

    // Kiểm tra xem yêu cầu đã tồn tại chưa
    for (int i = 0; i < receiver_list->request_count; i++)
        if (receiver_list->add_friend_requests[i] == sender_id)
            return 0; // Yêu cầu đã tồn tại

    // Kiểm tra xem da la ban hay chua
    for (int i = 0; i < receiver_list->friend_count; i++)
        if (receiver_list->friends[i] == sender_id){
            char response[1024] = "ERROR|You friend already\n";
            send(sender_sockfd, response, strlen(response) ,0);
            return 0; // Yêu cầu đã tồn tại
        }

    // Thêm yêu cầu nếu danh sách chưa đầy
    if (receiver_list->request_count < MAX_REQUESTS) {
        receiver_list->add_friend_requests[receiver_list->request_count++] = sender_id;
        char response[1024] = "NOTIFICATION|You have new friend request\n";
        send(receiver_sockfd, response, strlen(response) ,0);
        return 1; // Thành công
    }

    return 0; // Danh sách yêu cầu đầy
}

int accept_friend_request(int sender_id, int receiver_id, int sender_sockfd) {
    friend_list_t * sender_list = get_friend_list_by_userid(sender_id);
    friend_list_t * receiver_list = get_friend_list_by_userid(receiver_id);

    if (!sender_list || !receiver_list)
        return 0; // Một trong hai không tồn tại

    // Kiểm tra và thêm bạn bè vào danh sách
    if (add_friend(sender_id, receiver_id) && add_friend(receiver_id, sender_id)) {
        // Xóa yêu cầu từ danh sách của người nhận
        for (int i = 0; i < receiver_list->request_count; i++)
            if (receiver_list->add_friend_requests[i] == sender_id) {
                for (int j = i; j < receiver_list->request_count - 1; j++)
                    receiver_list->add_friend_requests[j] = receiver_list->add_friend_requests[j+1];
                
                receiver_list->request_count--;

                char response[1024] = "NOTIFICATION|Your friend request has been accepted\n";
                send(sender_sockfd, response, strlen(response) ,0);
                return 1; // Thành công
            }
    }

    return 0; // Thất bại
}

int decline_friend_request(int receiver_id, int sender_id) {
    friend_list_t * receiver_list = get_friend_list_by_userid(receiver_id);
    if (!receiver_list)
        return 0; // Người nhận không tồn tại

    // Tìm và xóa yêu cầu kết bạn
    for (int i = 0; i < receiver_list->request_count; i++)
        if (receiver_list->add_friend_requests[i] == sender_id) {
            for (int j = i; j < receiver_list->request_count - 1; j++)
                receiver_list->add_friend_requests[j] = receiver_list->add_friend_requests[j + 1];
            receiver_list->request_count--;
            return 1; // Thành công
        }

    return 0; // Không tìm thấy yêu cầu
}

void view_friend_requests(client_t * user_list, client_t * client) {
    friend_list_t * friend_list = get_friend_list_by_userid(client->uid);
    if (!friend_list)
        return; // Người dùng không tồn tại

    if (friend_list->request_count == 0)
        return; // Không có yêu cầu

    // Tạo buffer để chứa danh sách yêu cầu
    char requests[1024] = "FRIEND_REQUEST|";

    // Duyệt qua các yêu cầu và thêm vào buffer
    for (int i = 0; i < friend_list->request_count; i++) {
        client_t * user = findUserById(user_list, friend_list->add_friend_requests[i]);
        strcat(requests, user->name);
        if (i < client->room_count - 1)
            strcat(requests, ",");
    }

    strcat(requests, "\n");
    send(client->sockfd, requests, strlen(requests), 0);
}