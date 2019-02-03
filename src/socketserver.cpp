#include <thread>
#include <sstream>
#include <utility>

#include "stx/socketserver.hpp"
#include "stx/socket.hpp"
#include "stx/logger.hpp"



namespace stx {

static constexpr stx::Logger logger("SocketServer");


SocketServer::SocketServer(int domain, int type, int protocol) :
    m_socket(domain, type, protocol)
{
    m_threaded = true;
}

void SocketServer::bind(NetworkAddress addr)
{
    m_socket.bind(addr);
}

void SocketServer::close()
{
    m_socket.close();
}

void SocketServer::listenForever()
{
    m_socket.listen(5);

    while (true) {
        auto peer = std::make_shared<Socket>(m_socket.accept());

        if (m_threaded) {
            std::thread handler_thread(m_handler, this, peer);
            logger.trace(
                "Starting new handler thread with id %",
                to_str_ss(handler_thread.get_id()));
            handler_thread.detach();
        } else {
            m_handler(this, peer);
        }
    }
}

void SocketServer::setHandler(ConnectionHandler handler)
{
    m_handler = handler;
}

ConnectionHandler SocketServer::getHandler() const
{
    return m_handler;
}

Socket& SocketServer::getSocketRef()
{
    return m_socket;
}

void SocketServer::setThreaded(bool threaded)
{
    m_threaded = threaded;
}

bool SocketServer::getThreaded() const
{
    return m_threaded;
}

TcpServer::TcpServer(NetworkAddress addr, ConnectionHandler handler) :
    SocketServer(AF_INET, SOCK_STREAM, 0)
{
    bind(addr);
    setHandler(handler);
}

UdpServer::UdpServer(NetworkAddress addr, ConnectionHandler handler) :
    SocketServer(AF_INET, SOCK_STREAM, 0)
{
    bind(addr);
    setHandler(handler);
}

}
