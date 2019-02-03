#pragma once
#include <memory>

#include "stx/socket.hpp"



namespace stx {

class SocketServer;

using ConnectionHandler = void(*)(SocketServer* server, std::shared_ptr<Socket> socket);


class SocketServer
{
public:
    SocketServer(int domain, int type, int protocol);
    SocketServer(const SocketServer& other) = delete;
    SocketServer& operator=(const SocketServer& other) = delete;

    void bind(NetworkAddress addr);
    void close();
    [[noreturn]] void listenForever();

    void setHandler(ConnectionHandler handler);
    ConnectionHandler getHandler() const;
    Socket& getSocketRef();
    void setThreaded(bool threaded);
    bool getThreaded() const;

private:
    Socket m_socket;
    ConnectionHandler m_handler;
    bool m_threaded;
};

class TcpServer : public SocketServer
{
public:
    TcpServer(NetworkAddress addr, ConnectionHandler handler);
};

class UdpServer : public SocketServer
{
public:
    UdpServer(NetworkAddress addr, ConnectionHandler handler);
};

}
