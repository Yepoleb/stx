#include <array>
#include <vector>
#include <string>
#include <cstring>
#include <stdint.h>
#include <cassert>

#include "stx/ipaddress.hpp"
#include "stx/string.hpp"
#include "stx/integer.hpp"
#include "stx/types.hpp"



namespace stx {

IpAddress::IpAddress()
{
    data = {};
}

IpAddress::IpAddress(
    uint16_t bl1, uint16_t bl2, uint16_t bl3, uint16_t bl4,
    uint16_t bl5, uint16_t bl6, uint16_t bl7, uint16_t bl8)
{
    std::array<uint16_t, 8> data_u16;
    data_u16[0] = stx::swap_be_u16(bl1);
    data_u16[1] = stx::swap_be_u16(bl2);
    data_u16[2] = stx::swap_be_u16(bl3);
    data_u16[3] = stx::swap_be_u16(bl4);
    data_u16[4] = stx::swap_be_u16(bl5);
    data_u16[5] = stx::swap_be_u16(bl6);
    data_u16[6] = stx::swap_be_u16(bl7);
    data_u16[7] = stx::swap_be_u16(bl8);
    pun_set(data.data(), data_u16);
}

IpAddress::IpAddress(const std::vector<char>& byte_data) :
    IpAddress(byte_data.data())
{
    assert(byte_data.size() == IPV6_SIZE);
}

IpAddress::IpAddress(const std::array<char, IPV6_SIZE>& byte_data) :
    IpAddress(byte_data.data())
{
    assert(byte_data.size() == IPV6_SIZE);
}

IpAddress::IpAddress(const char* byte_data)
{
    std::memcpy(data.data(), byte_data, IPV6_SIZE);
}

IpAddress::IpAddress(uint32_t ipv4)
{
    std::array<uint32_t, 4> data_u32;
    data_u32[0] = 0;
    data_u32[1] = 0;
    data_u32[2] = stx::swap_be_u32(0x0000FFFF);
    data_u32[3] = ipv4;
    pun_set(data.data(), data_u32);
}

bool IpAddress::operator==(const IpAddress& other) const
{
    for (size_t i = 0; i < IPV6_SIZE; i++) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

bool IpAddress::operator!=(const IpAddress& other) const
{
    return !(*this == other);
}

IpAddress::operator bool() const
{
    return isNull();
}

bool IpAddress::operator!() const
{
    return !isNull();
}

uint8_t IpAddress::getOctet(IpType t, size_t index) const
{
    if (t == IpType::IPv4) {
        assert(index < IPV4_SIZE);
        return data[12 + index];
    } else {
        assert(index < IPV6_SIZE);
        return data[index];
    }
}

uint16_t IpAddress::getBlock(size_t index) const
{
    return stx::swap_be_u16(pun_get<uint16_t>(data.data(), index));
}

void IpAddress::setOctet(IpType t, size_t index, uint8_t value)
{
    if (t == IpType::IPv4) {
        assert(index < IPV4_SIZE);
        data[12 + index] = value;
    } else {
        assert(index < IPV6_SIZE);
        data[index] = value;
    }
}

void IpAddress::setBlock(size_t index, uint16_t value)
{
    pun_set(data.data(), index, stx::swap_be_u16(value));
}

IpAddress IpAddress::mask(IpType t, size_t bits) const
{
    IpAddress ret(*this);
    size_t start_i = (t == IpType::IPv4) ? 12 : 0;
    for (size_t octet_i = start_i; octet_i < IPV6_SIZE; octet_i++) {
        ret.data[octet_i] &= reverse_bitmask_u8(bits);
        bits = stx::constrain_max(bits - 8, 0_size);
    }
    return ret;
}

bool IpAddress::isNull() const
{
    for (char octet : data) {
        if (octet != 0) return false;
    }
    return true;
}

IpType IpAddress::getType() const
{
    const IpAddress IPV4_PREFIX(0, 0, 0, 0, 0, 0xFFFF, 0, 0);
    const size_t IPV4_PREFIX_LEN = 12;

    for (size_t i = 0; i < IPV4_PREFIX_LEN; i++) {
        if (data[i] != IPV4_PREFIX.data[i]) {
            return IpType::IPv6;
        }
    }
    return IpType::IPv4;
}

std::string IpAddress::formatIPv4() const
{
    return stx::format(
        "%.%.%.%", (int)data[12], (int)data[13], (int)data[14], (int)data[15]);
}

std::string IpAddress::formatIPv6() const
{
    bool was_null = false;
    ssize_t max_null_pos = -1;
    ssize_t max_null_count = 1;
    ssize_t cur_null_pos = -1;
    ssize_t cur_null_count = 1;
    for (ssize_t block_i = 0; block_i < IPV6_BLOCKS; block_i++) {
        if (getBlock(block_i) == 0) {
            if (!was_null) {
                cur_null_pos = block_i;
                cur_null_count = 1;
            } else {
                cur_null_count++;
            }

            if (cur_null_count > max_null_count) {
                max_null_pos = cur_null_pos;
                max_null_count = cur_null_count;
            }

            was_null = true;
        } else {
            was_null = false;
        }
    }

    std::stringstream ss;
    ss << std::hex;
    ssize_t block_i = 0;
    while (block_i < IPV6_BLOCKS) {
        if (block_i == max_null_pos) {
            ss << ':';
            block_i += max_null_count;
            if (block_i == IPV6_BLOCKS) {
                ss << ':';
            }
        } else {
            if (block_i != 0) {
                ss << ':';
            }
            ss << getBlock(block_i);
            block_i++;
        }
    }

    return ss.str();
}

std::string IpAddress::toString() const
{
    if (getType() == IpType::IPv4) {
        return formatIPv4();
    } else {
        return formatIPv6();
    }
}

uint32_t IpAddress::toIPv4() const
{
    return stx::pun_get<uint32_t>(data.data(), 3);
}

std::array<char, IPV6_SIZE> IpAddress::toIPv6() const
{
    return stx::pun_get<std::array<char, IPV6_SIZE>>(data.data());
}

}
