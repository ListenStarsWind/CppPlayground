#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <thread>

#pragma comment(lib, "Ws2_32.lib")  // ���� Winsock ��

using namespace std;

// �ú궨�� IP �Ͷ˿�
#define REMOTE_IP    "127.0.0.1"  // Ĭ�� IP�����籾�ػػ���ַ
#define REMOTE_PORT  12345        // Ĭ�϶˿�

#define SOCKET_ERR   1
#define BUFFER_SIZE  1024

// Windows ��û��ֱ�ӵ� errno��ʹ�� WSAGetLastError
#define STRERROR(x) WSAGetLastError()

struct push_args
{
    SOCKET _fd;
    struct sockaddr_in _server;
};

void push(push_args* args)
{
    SOCKET& sockfd = args->_fd;
    struct sockaddr_in& remote = args->_server;
    string message;

    while (true)
    {
        cout << "Please Enter@ ";
        getline(cin, message);

        if (sendto(sockfd, message.c_str(), static_cast<int>(message.size()), 0,
            reinterpret_cast<const sockaddr*>(&remote), sizeof(remote)) == SOCKET_ERROR)
        {
            cout << "sendto error: " << STRERROR(errno) << endl;
        }
    }
}

void pull(SOCKET* args)
{
    SOCKET& sockfd = *args;
    char buffer[BUFFER_SIZE];
    while (true)
    {
        struct sockaddr_in temp;
        int size = sizeof(temp);
        int len = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
            reinterpret_cast<struct sockaddr*>(&temp), &size);
        if (len == SOCKET_ERROR)
        {
            cout << "recvfrom error: " << STRERROR(errno) << endl;
            continue;
        }
        buffer[len] = '\0';
        cerr << buffer;
    }
}

int main()
{
    // ��ʼ�� Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "WSAStartup failed: " << STRERROR(errno) << endl;
        return SOCKET_ERR;
    }

    SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd == INVALID_SOCKET)
    {
        cout << "socket create error: " << STRERROR(errno) << endl;
        WSACleanup();
        return SOCKET_ERR;
    }
    cout << "socket create success, sockfd: " << sockfd << endl;

    // ʹ�ú궨��� IP �Ͷ˿�
    struct sockaddr_in remote;
    remote.sin_family = AF_INET;
    remote.sin_port = htons(static_cast<u_short>(REMOTE_PORT));  // �ú궨��Ķ˿�
    remote.sin_addr.s_addr = inet_addr(REMOTE_IP);              // �ú궨��� IP

    struct push_args i;
    i._fd = sockfd;
    i._server = remote;

    // �����߳�
    thread out(push, &i);
    thread in(pull, &sockfd);

    out.join();
    in.join();

    // ����
    closesocket(sockfd);
    WSACleanup();

    return 0;
}

// ����Ļ�û�б����Թ�
















#if 0

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

using namespace std;

#define SOCKET_ERR       1
#define BUFFER_SIZE      1024
#define REMOTE_IP        "120.55.90.240"  // Ĭ��IP��ַ�����ػػ���
#define REMOTE_PORT      8888        // Ĭ�϶˿ں�

// Link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

int main()
{
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        cout << "WSAStartup failed: " << iResult << endl;
        return 1;
    }

    // ʹ�ú궨���IP�Ͷ˿�
    string remote_ip = REMOTE_IP;
    unsigned short remote_port = REMOTE_PORT;

    SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd == INVALID_SOCKET)
    {
        cout << "socket create error: " << WSAGetLastError() << endl;
        WSACleanup();
        exit(SOCKET_ERR);
    }
    cout << "socket create success, sockfd: " << sockfd << endl;

    struct sockaddr_in remote;
    remote.sin_family = AF_INET;
    remote.sin_port = htons(remote_port);
    if (inet_pton(AF_INET, remote_ip.c_str(), &remote.sin_addr) <= 0) {
        cout << "inet_pton error: " << WSAGetLastError() << endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    string message;
    char buffer[BUFFER_SIZE];
    while (true)
    {
        cout << "Please Enter@ ";
        getline(cin, message);

        int sendResult = sendto(sockfd, message.c_str(), message.size(), 0,
            (struct sockaddr*)&remote, sizeof(remote));
        if (sendResult == SOCKET_ERROR)
        {
            cout << "sendto error: " << WSAGetLastError() << endl;
        }

        struct sockaddr_in temp;
        int size = sizeof(temp);
        int len = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
            (struct sockaddr*)&temp, &size);
        if (len == SOCKET_ERROR)
        {
            cout << "recvfrom error: " << WSAGetLastError() << endl;
            continue;
        }
        buffer[len] = '\0';
        cout << buffer;
    }

    // Cleanup
    closesocket(sockfd);
    WSACleanup();
    return 0;
}

#endif