#include "tcp_client.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/** Hostname */
static const char* HOST = "127.0.0.1";

/** Port */
static const int PORT = 1234;

/** Buffer size */
static const size_t BUF_SIZE = 20;

static int error_handler(const char* message, TcpClient* tcp_client) {
    tcp_client_cleanup(tcp_client);
    fprintf(stderr, "[Error] %s\n", message);
    return EXIT_FAILURE;
}

int main(void) {
    // 接続先ホスト・ポート設定
    TcpClient* tcp_client = tcp_client_initialize(HOST, PORT);

    // サーバー接続
    TCP_CLIENT_STATUS connected = tcp_client_attach(tcp_client);

    if (connected == TCP_CLIENT_STATUS_CREATE_SOCKET_ERROR ||
        connected == TCP_CLIENT_STATUS_CONNECTION_ERROR) {
        return error_handler("Failed connect", tcp_client);
    }

    // メッセージ送信
    const char* message = "Hello world";

    if (tcp_client_send(tcp_client, message) == TCP_CLIENT_STATUS_SEND_ERROR) {
        tcp_client_detach(tcp_client);
        return error_handler("Falied send data %s\n", tcp_client);
    }

    // メッセージ受信
    char receive_buf[BUF_SIZE];
    memset(receive_buf, 0, BUF_SIZE);

    int received = tcp_client_recieve(tcp_client, BUF_SIZE, receive_buf);

    if (received < TCP_CLIENT_STATUS_RECIEVE_ERROR) {
        tcp_client_detach(tcp_client);
        return error_handler("Falied receive data %s\n", tcp_client);
    }

    fprintf(stdout, "Receive data: %s\n", receive_buf);

    // コネクション開放
    tcp_client_cleanup(tcp_client);

    return EXIT_SUCCESS;
}
