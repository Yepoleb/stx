#pragma once
#include <vector>
#include <stddef.h>
#include <cstring>


namespace stx {

typedef std::vector<char> ByteArray;

inline void append(ByteArray& bytearray, const char* data, size_t length)
{
    size_t init_size = bytearray.size();
    bytearray.resize(init_size + length);
    std::memcpy(bytearray.data() + init_size, data, length);
}

}
