#pragma once
#include <cstring>
#include <stddef.h>



namespace stx {

typedef unsigned char uchar;
typedef std::make_signed<size_t>::type ssize_t;

template <typename T>
T pun_get(const void* src)
{
    T ret;
    std::memcpy(&ret, src, sizeof(T));
    return ret;
}

template <typename T>
T pun_get(const void* src, size_t index)
{
    T ret;
    const char* src_cp = static_cast<const char*>(src);
    std::memcpy(&ret, src_cp + index * sizeof(T), sizeof(T));
    return ret;
}

template <typename T>
void pun_set(void* dest, const T& value)
{
    std::memcpy(dest, &value, sizeof(T));
}

template <typename T>
void pun_set(void* dest, size_t index, const T& value)
{
    char* dest_cp = static_cast<char*>(dest);
    std::memcpy(dest_cp + index * sizeof(T), &value, sizeof(T));
}

}
