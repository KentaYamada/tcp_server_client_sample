#include "tcp_server.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

/** Buffer size */
static const size_t BUF_SIZE = 20;

/** Port */
static const u_int16_t PORT = 1234;

static int error_handler(const char* message, TcpServer* tcp_server) {
    fprintf(stderr, "[Error] %s\n", message);
    tcp_server_destroy(tcp_server);

    return EXIT_FAILURE;
}

int main(void) {
    TcpServer* tcp_server = tcp_server_initialize();

    if (tcp_server == NULL) {
        return error_handler("Failed create tcp_server object", tcp_server);
    }

    // ソケット生成
    if (tcp_server_create_socket(tcp_server, PORT) == TCP_SERVER_STATUS_CREATE_SOCKET_ERROR) {
        return error_handler("Failed create socket", tcp_server);
    }

    // サーバー接続開始
    TCP_SERVER_STATUS attached = tcp_server_attach(tcp_server);

    if (attached == TCP_SERVER_STATUS_BIND_ERROR) {
        return error_handler("Failed bind", tcp_server);
    }
    if (attached == TCP_SERVER_STATUS_ACCEPT_ERROR) {
        return error_handler("Failed attach client", tcp_server);
    }

    // メッセージ受信
    char buf[BUF_SIZE];
    memset(buf, 0, BUF_SIZE);

    if (tcp_server_receive(tcp_server, BUF_SIZE, buf) == TCP_SERVER_STATUS_RECIEVE_ERROR) {
        return error_handler("Failed receive data", tcp_server);
    }

    fprintf(stdout, "Receive data: %s\n", buf);

    // メッセージ送信
    if (tcp_server_send(tcp_server, BUF_SIZE, "I'm fine thank you") == TCP_SERVER_STATUS_SEND_ERROR) {
        return error_handler("Failed send data", tcp_server);
    }

    // コネクション開放
    tcp_server_destroy(tcp_server);

    return EXIT_SUCCESS;
}
