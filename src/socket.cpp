#include <stdint.h>
#include <assert.h>
#include <system_error>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>

#include "stx/socket.hpp"
#include "stx/logger.hpp"



namespace stx {

std::ostream& operator<<(std::ostream& stream, const NetworkAddress& addr)
{
    stream << addr.str();
    return stream;
}


NetworkAddress::NetworkAddress()
{
    host = 0;
    port = 0;
}

NetworkAddress::NetworkAddress(uint32_t host_, uint16_t port_)
{
    host = host_;
    port = port_;
}

sockaddr_in NetworkAddress::toSockaddrIn() const
{
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = htonl(host);

    return sa;
}

NetworkAddress NetworkAddress::fromSockaddrIn(const sockaddr_in& sa)
{
    NetworkAddress na;
    na.host = ntohl(sa.sin_addr.s_addr);
    na.port = ntohs(sa.sin_port);

    return na;
}

std::string NetworkAddress::str() const
{
    int a = (host >> 24);
    int b = (host >> 16) & 0xFF;
    int c = (host >> 8) & 0xFF;
    int d = host & 0xFF;

    std::stringstream ss;
    ss << a << '.' << b << '.' << c << '.' << d << ':' << port;
    return ss.str();
}



Socket::Socket()
{
    m_handle = -1;
}

Socket::Socket(int domain, int type, int protocol)
{
    assert(domain == AF_INET && protocol == 0);
    m_domain = domain;
    m_type = type;
    m_protocol = protocol;

    m_handle = socket(domain, type, protocol);
    if (m_handle == -1) {
        throw std::system_error(errno, std::system_category());
    }
}

Socket::Socket(int domain, int type, int protocol, socket_t handle)
{
    assert(domain == AF_INET && protocol == 0);
    m_domain = domain;
    m_type = type;
    m_protocol = protocol;

    m_handle = handle;
}

Socket::~Socket()
{
    close();
}

Socket::Socket(Socket&& other)
{
    m_domain = other.m_domain;
    m_type = other.m_type;
    m_protocol = other.m_protocol;
    m_handle = other.m_handle;

    other.m_handle = -1;
}

Socket Socket::accept()
{
    sockaddr_in peer_addr;
    socklen_t peer_addr_len = sizeof(sockaddr_in);
    socket_t peer_handle = ::accept(m_handle, (sockaddr*)&peer_addr, &peer_addr_len);
    if (peer_handle == -1) {
        throw std::system_error(errno, std::system_category());
    }

    return Socket(m_domain, m_type, m_protocol, peer_handle);
}

void Socket::bind(NetworkAddress addr)
{
    int optval = 1;
    setsockopt(m_handle, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));

    sockaddr_in sa = addr.toSockaddrIn();
    if (::bind(m_handle, (sockaddr*)&sa, sizeof(sockaddr_in))) {
        throw std::system_error(errno, std::system_category());
    }
}

void Socket::close()
{
    if (!isValid()) return;
    if (::close(m_handle)) {
        throw std::system_error(errno, std::system_category());
    }
}

void Socket::listen(int backlog)
{
    if (::listen(m_handle, backlog)) {
        throw std::system_error(errno, std::system_category());
    }
}

NetworkAddress Socket::getPeer()
{
    sockaddr_in sa;
    socklen_t sa_len = sizeof(sockaddr_in);
    if (::getpeername(m_handle, (sockaddr*)&sa, &sa_len) == -1) {
        throw std::system_error(errno, std::system_category());
    }
    return NetworkAddress::fromSockaddrIn(sa);
}

bool Socket::isValid() {
    return m_handle != -1;
}

int64_t Socket::readInto1(void* buffer, int64_t size)
{
    int64_t bytes_read = ::recv(m_handle, buffer, size, MSG_NOSIGNAL);
    if (bytes_read == -1) {
        throw std::system_error(errno, std::system_category());
    }
    return bytes_read;
}

int64_t Socket::write1(const void* buffer, int64_t size)
{
    int64_t bytes_written = ::send(m_handle, buffer, size, MSG_NOSIGNAL);
    if (bytes_written == -1) {
        throw std::system_error(errno, std::system_category());
    }
    return bytes_written;
}

//QByteArray Socket::read(int size)
//{
//    if (!size) return QByteArray();
//
//    QByteArray data(size, 0);
//    ssize_t sock_size = ::recv(m_handle, data.data(), size, MSG_WAITALL | MSG_NOSIGNAL);
//    if (sock_size == -1) {
//        throw std::system_error(errno, std::system_category());
//    }
//    if (sock_size < size) {
//        data.truncate(sock_size);
//    }
//    return data;
//}
//
//void Socket::write(QByteArray data)
//{
//    if (data.isEmpty()) return;
//
//    ssize_t sock_size = ::send(m_handle, data.data(), data.size(), MSG_NOSIGNAL);
//    if (sock_size == -1) {
//        throw std::system_error(errno, std::system_category());
//    }
//}

socket_t Socket::getHandle() {
    return m_handle;
}

}
