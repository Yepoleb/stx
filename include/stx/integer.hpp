#pragma once
#include <stdint.h>
#include <stddef.h>

#include "stx/algorithm.hpp"



namespace stx {

constexpr int8_t operator "" _s8(unsigned long long value)
{
    return static_cast<int8_t>(value);
}

constexpr uint8_t operator "" _u8(unsigned long long value)
{
    return static_cast<uint8_t>(value);
}

constexpr int16_t operator "" _s16(unsigned long long value)
{
    return static_cast<int16_t>(value);
}

constexpr uint16_t operator "" _u16(unsigned long long value)
{
    return static_cast<uint16_t>(value);
}

constexpr int32_t operator "" _s32(unsigned long long value)
{
    return static_cast<int32_t>(value);
}

constexpr uint32_t operator "" _u32(unsigned long long value)
{
    return static_cast<uint32_t>(value);
}

constexpr int64_t operator "" _s64(unsigned long long value)
{
    return static_cast<int64_t>(value);
}

constexpr uint64_t operator "" _u64(unsigned long long value)
{
    return static_cast<uint64_t>(value);
}

constexpr intmax_t operator "" _smax(unsigned long long value)
{
    return static_cast<intmax_t>(value);
}

constexpr uintmax_t operator "" _umax(unsigned long long value)
{
    return static_cast<uintmax_t>(value);
}

constexpr intptr_t operator "" _sptr(unsigned long long value)
{
    return static_cast<intptr_t>(value);
}

constexpr uintptr_t operator "" _uptr(unsigned long long value)
{
    return static_cast<uintptr_t>(value);
}

constexpr ptrdiff_t operator "" _ptrdiff(unsigned long long value)
{
    return static_cast<ptrdiff_t>(value);
}

constexpr size_t operator "" _size(unsigned long long value)
{
    return static_cast<size_t>(value);
}



// There doesn't seem to be a way to make this constexpr :(
inline bool is_big_endian()
{
    int x = 1;
    return (*reinterpret_cast<char*>(&x) == 0);
}

inline bool is_little_endian()
{
    return !is_big_endian();
}

constexpr uint16_t byteswap_u16(uint16_t value)
{
    return static_cast<uint16_t>((value >> 8) | (value << 8));
}

constexpr uint32_t byteswap_u32(uint32_t value)
{
    return ((value >> 24) & 0x000000FF) | ((value >>  8) & 0x0000FF00) |
           ((value <<  8) & 0x00FF0000) | ((value << 24) & 0xFF000000);
}

constexpr uint64_t byteswap_u64(uint64_t value)
{
    return ((value >> 56) & 0x00000000000000FF) |
           ((value >> 40) & 0x000000000000FF00) |
           ((value >> 24) & 0x0000000000FF0000) |
           ((value >>  8) & 0x00000000FF000000) |
           ((value <<  8) & 0x000000FF00000000) |
           ((value << 24) & 0x0000FF0000000000) |
           ((value << 40) & 0x00FF000000000000) |
           ((value << 56) & 0xFF00000000000000);
}


inline uint16_t swap_be_u16(uint16_t value)
{
    if (is_little_endian()) {
        return byteswap_u16(value);
    } else {
        return value;
    }
}

inline uint32_t swap_be_u32(uint32_t value)
{
    if (is_little_endian()) {
        return byteswap_u32(value);
    } else {
        return value;
    }
}

inline uint64_t swap_be_u64(uint64_t value)
{
    if (is_little_endian()) {
        return byteswap_u64(value);
    } else {
        return value;
    }
}

inline uint16_t swap_le_u16(uint16_t value)
{
    if (is_big_endian()) {
        return byteswap_u16(value);
    } else {
        return value;
    }
}

inline uint32_t swap_le_u32(uint32_t value)
{
    if (is_big_endian()) {
        return byteswap_u32(value);
    } else {
        return value;
    }
}

inline uint64_t swap_le_u64(uint64_t value)
{
    if (is_big_endian()) {
        return byteswap_u64(value);
    } else {
        return value;
    }
}


constexpr uint64_t bitmask_u64(size_t bits)
{
    return (~0_u64 >> (64 - stx::constrain_max(bits, 64_size)));
}

constexpr uint32_t bitmask_u32(size_t bits)
{
    return (~0_u32 >> (32 - stx::constrain_max(bits, 32_size)));
}

constexpr uint16_t bitmask_u16(size_t bits)
{
    return (uint16_t)(~0_u16 >> (16 - stx::constrain_max(bits, 16_size)));
}

constexpr uint8_t bitmask_u8(size_t bits)
{
    return (uint8_t)(~0_u8 >> (8 - stx::constrain_max(bits, 8_size)));
}


constexpr uint64_t reverse_bitmask_u64(size_t bits)
{
    return (~0_u64 << (64 - stx::constrain_max(bits, 64_size)));
}

constexpr uint32_t reverse_bitmask_u32(size_t bits)
{
    return (~0_u32 << (32 - stx::constrain_max(bits, 32_size)));
}

constexpr uint16_t reverse_bitmask_u16(size_t bits)
{
    return (uint16_t)(~0_u16 << (16 - stx::constrain_max(bits, 16_size)));
}

constexpr uint8_t reverse_bitmask_u8(size_t bits)
{
    return (uint8_t)(~0_u8 << (8 - stx::constrain_max(bits, 8_size)));
}

}
