#pragma once
#include <stdint.h>
#include <stddef.h>
#include <string>
#include <sstream>
#include <vector>
#include <array>

#include "stx/bytearray.hpp"



namespace stx {

template <typename T>
struct StringConverter
{
    std::string operator()(const T& val)
    {
        return val.str();
    }
};

template <typename T>
std::string to_str(const T& val)
{
    return StringConverter<T>()(val);
}

template <typename T>
struct ReprConverter
{
    std::string operator()(const T& val)
    {
        return val.repr();
    }
};

template <typename T>
std::string to_repr(const T& val)
{
    return ReprConverter<T>()(val);
}

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

namespace detail {
    std::string to_repr(const std::string& val);
    std::string to_repr(const ByteArray& val);
    std::string to_hex(const ByteArray& val);
}

template <typename T>
struct StringConverterNumber
{
    std::string operator()(T val)
    {
        return std::to_string(val);
    }
};

template <>
struct StringConverter<std::string>
{
    std::string operator()(const std::string& val)
    {
        return val;
    }
};

template <>
struct StringConverter<const char*>
{
    std::string operator()(const char* val)
    {
        return val;
    }
};

template <>
struct StringConverter<int64_t> : public StringConverterNumber<int64_t> {};

template <>
struct StringConverter<int32_t> : public StringConverterNumber<int32_t> {};

template <>
struct StringConverter<int16_t> : public StringConverterNumber<int16_t> {};

template <>
struct StringConverter<uint64_t> : public StringConverterNumber<uint64_t> {};

template <>
struct StringConverter<uint32_t> : public StringConverterNumber<uint32_t> {};

template <>
struct StringConverter<uint16_t> : public StringConverterNumber<uint16_t> {};

template <>
struct StringConverter<float> : public StringConverterNumber<float> {};

template <>
struct StringConverter<double> : public StringConverterNumber<double> {};

template <>
struct StringConverter<long double> : public StringConverterNumber<long double> {};

template <>
struct StringConverter<char>
{
    std::string operator()(char val)
    {
        return std::string(1, val);
    }
};

template <>
struct StringConverter<unsigned char>
{
    std::string operator()(unsigned char val)
    {
        return std::string(1, val);
    }
};

template <>
struct StringConverter<bool>
{
    std::string operator()(bool val)
    {
        return val ? "true" : "false";
    }
};

template <>
struct StringConverter<ByteArray>
{
    std::string operator()(const ByteArray& val)
    {
        return std::string(val.data(), val.size());
    }
};

template <typename T, typename Allocator>
struct StringConverter<std::vector<T, Allocator>>
{
    std::string operator()(const std::vector<T, Allocator>& val)
    {
        return to_str_iter(val);
    }
};

template<typename T, size_t N>
struct StringConverter<std::array<T, N>>
{
    std::string operator()(const std::array<T, N>& val)
    {
        return to_str_iter(val);
    }
};



template <>
struct ReprConverter<std::string>
{
    std::string operator()(const std::string& val)
    {
        return detail::to_repr(val);
    }
};

template <>
struct ReprConverter<const char*>
{
    std::string operator()(const char* val)
    {
        return detail::to_repr(std::string(val));
    }
};

template <>
struct ReprConverter<int64_t> : public StringConverterNumber<int64_t> {};

template <>
struct ReprConverter<int32_t> : public StringConverterNumber<int32_t> {};

template <>
struct ReprConverter<int16_t> : public StringConverterNumber<int16_t> {};

template <>
struct ReprConverter<uint64_t> : public StringConverterNumber<uint64_t> {};

template <>
struct ReprConverter<uint32_t> : public StringConverterNumber<uint32_t> {};

template <>
struct ReprConverter<uint16_t> : public StringConverterNumber<uint16_t> {};

template <>
struct ReprConverter<float> : public StringConverterNumber<float> {};

template <>
struct ReprConverter<double> : public StringConverterNumber<double> {};

template <>
struct ReprConverter<long double> : public StringConverterNumber<long double> {};

template <>
struct ReprConverter<char>
{
    std::string operator()(char val)
    {
        return "'" + std::string(1, val) + "'";
    }
};

template <>
struct ReprConverter<unsigned char>
{
    std::string operator()(unsigned char val)
    {
        return "'" + std::string(1, val) + "'";
    }
};

template <>
struct ReprConverter<bool>
{
    std::string operator()(bool val)
    {
        return val ? "true" : "false";
    }
};

template <>
struct ReprConverter<ByteArray>
{
    std::string operator()(const ByteArray& val)
    {
        return detail::to_repr(val);
    }
};

// TODO: Make these more generic

std::string to_hex(char val);
std::string to_hex(const ByteArray& val);
ByteArray to_bytes(const std::string& str);
bool to_bool(const std::string& str);

}
