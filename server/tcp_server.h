#ifndef _TCP_SERVER_H__
#define _TCP_SERVER_H__

#include <stddef.h>
#include <sys/types.h>

typedef enum {
    TCP_SERVER_STATUS_OK = 0,
    TCP_SERVER_STATUS_INITIALIZE_ERROR = -1,
    TCP_SERVER_STATUS_CREATE_SOCKET_ERROR = -2,
    TCP_SERVER_STATUS_BIND_ERROR = -3,
    TCP_SERVER_STATUS_LISTEN_ERROR = -4,
    TCP_SERVER_STATUS_ACCEPT_ERROR = -5,
    TCP_SERVER_STATUS_RECIEVE_ERROR = -6,
    TCP_SERVER_STATUS_SEND_ERROR = -7
} TCP_SERVER_STATUS;

typedef struct tcp_server_t TcpServer;

/**
 * TCPServerオブジェクト生成
 */
extern TcpServer* tcp_server_initialize();

/**
 * ソケット生成
 */
extern TCP_SERVER_STATUS tcp_server_create_socket(TcpServer* tcp_server, const u_int16_t port);

/**
 * クライアントとの接続
 */
extern TCP_SERVER_STATUS tcp_server_attach(TcpServer* tcp_server);

/**
 * クライアントからのデータを受信
 */
extern TCP_SERVER_STATUS tcp_server_receive(const TcpServer* tcp_server, const size_t buf_size, char* buf);

/**
 * クライアントからのデータを送信
 */
extern TCP_SERVER_STATUS tcp_server_send(const TcpServer* tcp_server, const size_t buf_size, const char* buf);

/**
 * ソケット破棄
 */
extern void tcp_server_destroy_socket(TcpServer* tcp_server);

/**
 * TcpServerオブジェクト破棄
 */
extern void tcp_server_destroy(TcpServer* tcp_server);

#endif // _TCP_SERVER_H__
