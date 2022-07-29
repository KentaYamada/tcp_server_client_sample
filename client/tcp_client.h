#ifndef _TCP_CLIENT_H__
#define _TCP_CLIENT_H__

#include <stddef.h>

typedef enum {
    TCP_CLIENT_STATUS_OK = 0,
    TCP_CLIENT_STATUS_CREATE_SOCKET_ERROR = -1,
    TCP_CLIENT_STATUS_CONNECTION_ERROR = -2,
    TCP_CLIENT_STATUS_CONNECTION_CLOSE_ERROR = -3,
    TCP_CLIENT_STATUS_SEND_ERROR = -4,
    TCP_CLIENT_STATUS_RECIEVE_ERROR = -5
} TCP_CLIENT_STATUS;

typedef struct tcp_client_t TcpClient;

/**
 * TCPClient初期化
 */
extern TcpClient* tcp_client_initialize(const char* host, const int port);

/**
 * TCPClientクリーンアップ
 */
extern void tcp_client_cleanup(TcpClient* tcp_client);

/**
 * 接続
 */
extern TCP_CLIENT_STATUS tcp_client_attach(TcpClient* tcp_client);

/**
 * 切断
 */
extern TCP_CLIENT_STATUS tcp_client_detach(TcpClient* tcp_client);

/**
 * 送信
 */
extern TCP_CLIENT_STATUS tcp_client_send(const TcpClient* tcp_client, const char* message);

/**
 * 受信
 */
extern TCP_CLIENT_STATUS tcp_client_recieve(const TcpClient* tcp_client, const size_t buf_size, char* buf);

#endif // _TCP_CLIENT_H__
