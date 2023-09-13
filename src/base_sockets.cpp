#include "base_sockets.hpp"

namespace woo200
{   
    ClientSocket::ClientSocket(int socket_family, int socket_type, int protocol)
    {
        this->sock = socket(socket_family, socket_type, protocol);
        this->remote_addr.sin_family = socket_family;
        this->connected = false;
    }
    ClientSocket::ClientSocket(int sock, sockaddr_in addr)
    {
        this->sock = sock;
        this->remote_addr = addr;

        this->connected = true;
    }
    ClientSocket::~ClientSocket()
    {
        this->close();
    }

    sockaddr_in ClientSocket::get_addr()
    {
        return this->remote_addr;
    }
    int ClientSocket::connect()
    {
        if (this->connected)
            return -2;

        int res = ::connect(this->sock, (struct sockaddr*) &this->remote_addr, sizeof(this->remote_addr));
        if (res >= 0)
            this->connected = true;

        return res;
    }
    int ClientSocket::connect(int port, const char* ip)
    {
        this->remote_addr.sin_port = htons(port);
        if (inet_pton(AF_INET, ip, &this->remote_addr.sin_addr) <= 0)
            return -1;

        return this->connect();
    }
    int ClientSocket::connect(sockaddr_in* addr)
    {
        this->remote_addr = *addr;
        return this->connect();
    }
    int ClientSocket::send(void* msg, int len)
    {
        return ::send(this->sock, msg, len, 0);
    }
    int ClientSocket::recv(void* buf, int len, int flags)
    {
        return ::recv(this->sock, buf, len, flags);
    }
    void ClientSocket::close()
    {
        ::close(this->sock);
    }

    ServerSocket::ServerSocket(int socket_family, int socket_type, int protocol)
    {
        this->sock = socket(socket_family, socket_type, protocol);
        this->bind_addr.sin_family = socket_family;
    }
    ServerSocket::~ServerSocket()
    {
        this->close();
    }

    void ServerSocket::close()
    {
        ::close(this->sock);
    }
    int ServerSocket::bind(const char* address, int port)
    {
        this->bind_addr.sin_port = htons(port);
        if (inet_pton(AF_INET, address, &this->bind_addr.sin_addr) <= 0)
        {
            return -1;
        }
        return ::bind(this->sock, (struct sockaddr*) &this->bind_addr, sizeof(this->bind_addr));
    }
    int ServerSocket::bind(sockaddr_in* addr)
    {
        this->bind_addr = *addr;
        ::setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, (const char*) &addr, sizeof(addr));
        return ::bind(this->sock, (struct sockaddr*) &this->bind_addr, sizeof(this->bind_addr));
    }
    int ServerSocket::listen(int backlog)
    {
        return ::listen(this->sock, backlog);
    }
    ClientSocket* ServerSocket::accept()
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_sock = ::accept(this->sock, (struct sockaddr*) &client_addr, &client_addr_len);
        ClientSocket* client = new ClientSocket(client_sock, client_addr);

        return client;
    }
}
