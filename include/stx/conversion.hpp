#pragma once
#include <stdint.h>
#include <stddef.h>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include "stx/bytearray.hpp"

//TODO: remove str() method from objects and overload to_str instead



namespace stx {

std::string to_str(std::string val);
std::string to_str(const char* val);
std::string to_str(int64_t val);
std::string to_str(int32_t val);
std::string to_str(int16_t val);
std::string to_str(uint64_t val);
std::string to_str(uint32_t val);
std::string to_str(uint16_t val);
std::string to_str(float val);
std::string to_str(double val);
std::string to_str(long double val);
std::string to_str(char val);
std::string to_str(unsigned char val);
std::string to_str(bool val);
std::string to_str(const ByteArray& val);

std::string to_repr(const std::string& val);
std::string to_repr(int64_t val);
std::string to_repr(int32_t val);
std::string to_repr(int16_t val);
std::string to_repr(uint64_t val);
std::string to_repr(uint32_t val);
std::string to_repr(uint16_t val);
std::string to_repr(float val);
std::string to_repr(double val);
std::string to_repr(long double val);
std::string to_repr(char val);
std::string to_repr(unsigned char val);
std::string to_repr(bool val);
std::string to_repr(const ByteArray& val);

std::string to_hex(const ByteArray& val);
ByteArray to_bytes(const std::string& str);
bool to_bool(const std::string& str);

template<typename T>
std::string to_str_ss(const T& arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

// Iterable stringifier
template<typename T>
std::string to_str_iter(const T& val)
{
    std::stringstream ss;
    ss << '[';
    auto begin = val.cbegin();
    auto end = val.cend();
    for (auto it = begin; it != end; ++it) {
        if (it != begin) {
            ss << ", ";
        }
        ss << stx::to_repr(*it);
    }
    ss << ']';

    return ss.str();
}

template<typename T>
std::string to_str_map(const T& val)
{
    std::stringstream ss;
    ss << '{';
    auto begin = val.cbegin();
    auto end = val.cend();
    for (auto it = begin; it != end; ++it) {
        if (it != begin) {
            ss << ", ";
        }
        const auto& map_pair = *it;
        ss << to_repr(map_pair.first) << ": "
            << to_repr(map_pair.second);
    }
    ss << '}';

    return ss.str();
}


template<typename T>
std::string to_str(const std::vector<T>& val)
{
    return to_str_iter(val);
}

template<typename T, size_t N>
std::string to_str(const std::array<T, N>& val)
{
    return to_str_iter(val);
}

template<typename T>
std::string to_str(const std::set<T>& val)
{
    return to_str_iter(val);
}

template<typename T>
std::string to_str(const std::multiset<T>& val)
{
    return to_str_iter(val);
}

template<typename T>
std::string to_str(const std::unordered_set<T>& val)
{
    return to_str_iter(val);
}

template<typename T>
std::string to_str(const std::unordered_multiset<T>& val)
{
    return to_str_iter(val);
}

template<typename T, typename U>
std::string to_str(const std::map<T, U>& val)
{
    return to_str_map(val);
}

template<typename T, typename U>
std::string to_str(const std::multimap<T, U>& val)
{
    return to_str_map(val);
}

template<typename T, typename U>
std::string to_str(const std::unordered_map<T, U>& val)
{
    return to_str_map(val);
}

template<typename T, typename U>
std::string to_str(const std::unordered_multimap<T, U>& val)
{
    return to_str_map(val);
}

}
