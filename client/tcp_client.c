#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "tcp_client.h"

struct tcp_client_t {
    struct sockaddr_in destination; /** 接続先 */
    int destination_sock_fd; /** ソケットファイルディスクリプタ */
};

TcpClient* tcp_client_initialize(const char *host, const int port) {
    TcpClient* tcp_client = (TcpClient*)malloc(sizeof(TcpClient));
    tcp_client->destination.sin_family = AF_INET;
    tcp_client->destination.sin_addr.s_addr = inet_addr(host);
    tcp_client->destination.sin_port = htons(port);

    return tcp_client;
}

void tcp_client_cleanup(TcpClient *tcp_client) {
    tcp_client_detach(tcp_client);
    free(tcp_client);
}

TCP_CLIENT_STATUS tcp_client_attach(TcpClient *tcp_client) {
    tcp_client->destination_sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (tcp_client->destination_sock_fd < 0) {
        return TCP_CLIENT_STATUS_CREATE_SOCKET_ERROR;
    }

    int connected = connect(tcp_client->destination_sock_fd, (struct sockaddr*)&tcp_client->destination, sizeof(tcp_client->destination));

    if (connected < 0) {
        tcp_client_detach(tcp_client);
        return TCP_CLIENT_STATUS_CONNECTION_ERROR;
    }

    return TCP_CLIENT_STATUS_OK;
}

TCP_CLIENT_STATUS tcp_client_detach(TcpClient *tcp_client) {
    if (close(tcp_client->destination_sock_fd) < 0) {
        return TCP_CLIENT_STATUS_CONNECTION_CLOSE_ERROR;
    }

    return TCP_CLIENT_STATUS_OK;
}

TCP_CLIENT_STATUS tcp_client_send(const TcpClient* tcp_client, const char *message) {
    size_t length = strlen(message);

    if (send(tcp_client->destination_sock_fd, message, length, 0) < 0) {
        return TCP_CLIENT_STATUS_SEND_ERROR;
    }

    return TCP_CLIENT_STATUS_OK;
}

TCP_CLIENT_STATUS tcp_client_recieve(const TcpClient* tcp_client, const size_t buf_size, char *buf) {
    if (recv(tcp_client->destination_sock_fd, buf, buf_size, 0) < 0) {
        return TCP_CLIENT_STATUS_RECIEVE_ERROR;
    }

    return TCP_CLIENT_STATUS_OK;
}
