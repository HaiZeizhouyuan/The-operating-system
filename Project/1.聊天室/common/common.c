/*************************************************************************
	> File Name: common.c
	> Author: 
	> Mail: 
	> Created Time: Sat Aug  8 14:32:12 2020
 ************************************************************************/

#include "head.h"

char conf_value_ans[512] = {0};
int make_non_block (int fd) {
    int flag;
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        return -1;
    }
    flag |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flag);
    return 0;
}

int make_block(int fd) {
    int flag;
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        return -1;
    }
    flag &= ~O_NONBLOCK;
    fcntl(fd, F_SETFL, flag);
}
//查找字符
char *get_conf(const char *conf, const char *key) {
    FILE *fr = NULL;
    if (conf == NULL || key == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if ((fr = fopen(conf, "r")) == NULL) {
        return NULL;
    }
    char *line = NULL, *sub = NULL;
    ssize_t nread, len;
    //static char conf_value_ans[512] = {0};
    while ((nread = getline(&line, &len, fr)) != -1) {
        if ((sub = strstr(line, key)) == NULL) continue;
        if (line[strlen(key)] == '=') {
            strncpy(conf_value_ans, sub + strlen(key) + 1, nread - strlen(key) - 2);
            *(conf_value_ans + nread - strlen(key) - 2) = '\0';
            break;
        }
    }
    free(line);
    fclose(fr);
    //if (!strlen(conf_value_ans)) return NULL;
    if (sub == NULL) return NULL;
    return conf_value_ans;
}
//服务端的建立
int socket_create(int port) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { //int socket(int domain, int type, int protocal);
        return -1;
    }
    //重启地址
    int val = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,(const char*)&val, sizeof(int)) < 0) {
        return -1;
    }
    struct sockaddr_in server;//创建表单名server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);//本地字节序转换成网络字节序的短整形
    server.sin_addr.s_addr = inet_addr("0.0.0.0");//所有的都要
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }

    if (listen(sockfd, 10) < 0) {
        return -1;
    }
    return sockfd;
}
//客户端的建立
int socket_connect(char *ip, int port){
    int sockfd;//创建端口名
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }
    return sockfd;
}

int socket_connect_timeout(char *host, int port, long timeout) {
    int sockfd;
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(host);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
    make_non_block(sockfd);
    
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = timeout;

    fd_set wfds;
    FD_ZERO(&wfds);
    FD_SET(sockfd, &wfds);

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        int retval, error = -1;
        int len = sizeof(int);
        retval = select(sockfd + 1, NULL, &wfds, NULL, &tv);
        if (retval < 0) {
            close(sockfd);
            return -1;
        } else if (retval) {
            if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&len) < 0) {
                close(sockfd);
                return -1;
            }
            if (error) {
                close(sockfd);
                return -1;
            }
        } else {
            printf("Connect Time Out!\n");
            close(sockfd);
            return -1;
        }
    }
    make_block(sockfd);
    return sockfd;
}
