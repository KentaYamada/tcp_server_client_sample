#include "tcp_server.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

struct tcp_server_t {
    int socket_fd; /* socket file discriptor */
    int client_socket_fd; /* client side socket file discriptor */
    struct sockaddr_in addr; /* server side connection info */
    struct sockaddr_in from_addr; /**/
    socklen_t len; /* accept length */
};

static bool tcp_server_is_null(const TcpServer* tcp_server) {
    return tcp_server == NULL;
}

TcpServer* tcp_server_initialize() {
    TcpServer* tcp_server = (TcpServer*)malloc(sizeof(TcpServer));
    return tcp_server;
}

TCP_SERVER_STATUS tcp_server_create_socket(TcpServer* tcp_server, const uint16_t port) {
    if (tcp_server_is_null(tcp_server)) {
        return TCP_SERVER_STATUS_INITIALIZE_ERROR;
    }

    tcp_server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (tcp_server->socket_fd < 0) {
        return TCP_SERVER_STATUS_BIND_ERROR;
    }

    // 待受用IP、ポート設定
    tcp_server->addr.sin_family = AF_INET;
    tcp_server->addr.sin_port = htons(port);
    tcp_server->addr.sin_addr.s_addr = INADDR_ANY;

    return TCP_SERVER_STATUS_OK;
}

TCP_SERVER_STATUS tcp_server_attach(TcpServer* tcp_server) {
    int binded = bind(tcp_server->socket_fd, (struct sockaddr*)&tcp_server->addr, sizeof(struct sockaddr_in));

    if (binded < 0) {
        return TCP_SERVER_STATUS_BIND_ERROR;
    }
    if (listen(tcp_server->socket_fd, SOMAXCONN) < 0) {
        return TCP_SERVER_STATUS_LISTEN_ERROR;
    }

    tcp_server->client_socket_fd = accept(tcp_server->socket_fd, (struct sockaddr*)&tcp_server->from_addr, &tcp_server->len);

    if (tcp_server->client_socket_fd < 0) {
        return TCP_SERVER_STATUS_ACCEPT_ERROR;
    }

    return TCP_SERVER_STATUS_OK;
}

TCP_SERVER_STATUS tcp_server_receive(const TcpServer* tcp_server, const size_t buf_size, char* buf) {
    int recieve_size = recv(tcp_server->client_socket_fd, buf, buf_size, 0);

    if (recieve_size < 0) {
        return TCP_SERVER_STATUS_RECIEVE_ERROR;
    }

    return TCP_SERVER_STATUS_OK;
}

TCP_SERVER_STATUS tcp_server_send(const TcpServer* tcp_server, const size_t buf_size, const char* buf) {
    ssize_t ret = write(tcp_server->client_socket_fd, buf, buf_size);

    if (ret < 0) {
        return TCP_SERVER_STATUS_SEND_ERROR;
    }

    return TCP_SERVER_STATUS_OK;
}

void tcp_server_destroy_socket(TcpServer* tcp_server) {
    close(tcp_server->client_socket_fd);
    close(tcp_server->socket_fd);
}

void tcp_server_destroy(TcpServer* tcp_server) {
    tcp_server_destroy_socket(tcp_server);
    free(tcp_server);
}
