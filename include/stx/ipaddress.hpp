#pragma once
#include <array>
#include <vector>
#include <string>
#include <string_view>
#include <stdint.h>



namespace stx {

constexpr size_t IPV4_SIZE = 4;
constexpr size_t IPV6_SIZE = 16;
constexpr size_t IPV6_BLOCKS = 8;

enum class IpType
{
    IPv4,
    IPv6
};

class IpAddress
{
public:
    IpAddress();
    IpAddress(
        uint16_t bl1, uint16_t bl2, uint16_t bl3, uint16_t bl4,
        uint16_t bl5, uint16_t bl6, uint16_t bl7, uint16_t bl8);
    IpAddress(const std::array<char, IPV6_SIZE>& byte_data);
    IpAddress(const std::vector<char>& byte_data);
    IpAddress(const char* byte_data);
    IpAddress(uint32_t ipv4);

    bool operator==(const IpAddress& other) const;
    bool operator!=(const IpAddress& other) const;
    operator bool() const;
    bool operator!() const;

    uint8_t getOctet(IpType t, size_t index) const;
    uint16_t getBlock(size_t index) const;
    void setOctet(IpType t, size_t index, uint8_t value);
    void setBlock(size_t index, uint16_t value);
    IpAddress mask(IpType t, size_t bits) const;

    bool isNull() const;
    IpType getType() const;
    std::string formatIPv4() const;
    std::string formatIPv6() const;
    std::string toString() const;
    uint32_t toIPv4() const;
    std::array<char, IPV6_SIZE> toIPv6() const;

private:
    alignas(8) std::array<uint8_t, IPV6_SIZE> data;
};

}

namespace std {

template <>
struct hash<stx::IpAddress>
{
    typedef stx::IpAddress argument_type;
    typedef size_t result_type;
    result_type operator()(const argument_type& value) const noexcept
    {
        std::array<char, stx::IPV6_SIZE> ip_data = value.toIPv6();
        std::string_view strv(ip_data.data(), stx::IPV6_SIZE);
        return std::hash<std::string_view>()(strv);
    }
};

}
