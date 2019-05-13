#pragma once
#include <stdint.h>
#include <string>
#include <ostream>

#include <arpa/inet.h>

#include "stx/stream.hpp"



namespace stx {

typedef int socket_t;


class NetworkAddress;
std::ostream& operator<<(std::ostream& stream, const NetworkAddress& addr);


class NetworkAddress
{
public:
    NetworkAddress();
    NetworkAddress(uint32_t host, uint16_t port);

    sockaddr_in toSockaddrIn() const;
    static NetworkAddress fromSockaddrIn(const sockaddr_in& sa);
    std::string str() const;

    uint32_t host;
    uint16_t port;
};

class Socket : public BaseStream
{
public:
    Socket();
    Socket(int domain, int type, int protocol);
    Socket(int domain, int type, int protocol, socket_t handle);
    ~Socket() override;
    Socket(const Socket& other) = delete;
    Socket& operator=(Socket& other) = delete;
    Socket(Socket&& other);

    Socket accept();
    void bind(NetworkAddress addr);
    void close();
    void listen(int backlog);
    NetworkAddress getPeer();
    bool isValid();

    int64_t readInto1(void* buffer, int64_t size) override;
    int64_t write1(const void* buffer, int64_t size) override;

    socket_t getHandle();

private:
    int m_domain;
    int m_type;
    int m_protocol;

    socket_t m_handle;
};

constexpr uint32_t makeIPv4(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
    return (a << 24) | (b << 16) | (c << 8) | d;
}

}
