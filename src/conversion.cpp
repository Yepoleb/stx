#include <string>
#include <sstream>
#include <iomanip>

#include "stx/conversion.hpp"
#include "stx/bytearray.hpp"


#include <iostream>
namespace stx {

std::string to_str(std::string val)
{
    return val;
}

std::string to_str(const char* val)
{
    return std::string(val);
}

std::string to_str(int64_t val)
{
    return std::to_string(val);
}

std::string to_str(int32_t val)
{
    return std::to_string(val);
}

std::string to_str(int16_t val)
{
    return std::to_string(val);
}

std::string to_str(uint64_t val)
{
    return std::to_string(val);
}

std::string to_str(uint32_t val)
{
    return std::to_string(val);
}

std::string to_str(uint16_t val)
{
    return std::to_string(val);
}

std::string to_str(float val)
{
    return std::to_string(val);
}

std::string to_str(double val)
{
    return std::to_string(val);
}

std::string to_str(long double val)
{
    return std::to_string(val);
}

std::string to_str(char val)
{
    return std::string(&val, 1);
}

std::string to_str(unsigned char val)
{
    return std::string(reinterpret_cast<char*>(&val), 1);
}

std::string to_str(bool val)
{
    return val ? "true" : "false";
}

std::string to_str(const ByteArray& val)
{
    return std::string(val.data(), val.size());
}



std::string to_repr(int64_t val)
{
    return std::to_string(val);
}

std::string to_repr(int32_t val)
{
    return std::to_string(val);
}

std::string to_repr(int16_t val)
{
    return std::to_string(val);
}

std::string to_repr(uint64_t val)
{
    return std::to_string(val);
}

std::string to_repr(uint32_t val)
{
    return std::to_string(val);
}

std::string to_repr(uint16_t val)
{
    return std::to_string(val);
}

std::string to_repr(float val)
{
    return std::to_string(val);
}

std::string to_repr(double val)
{
    return std::to_string(val);
}

std::string to_repr(long double val)
{
    return std::to_string(val);
}

std::string to_repr(char val)
{
    std::stringstream ss;
    ss << '\'' << val << '\'';
    return ss.str();
}

std::string to_repr(unsigned char val)
{
    return to_repr(static_cast<char>(val));
}

std::string to_repr(bool val)
{
    return to_str(val);
}

std::string to_repr(const std::string& val)
{
    std::stringstream ss;
    ss << '"';
    for (char c : val) {
        if (c == '"') {
            ss << "\\\"";
        } else {
            ss << c;
        }
    }
    ss << '"';
    return ss.str();
}

std::string to_repr(const ByteArray& val)
{
    std::stringstream ss;
    ss << '"';
    ss << std::hex << std::setfill('0') << std::uppercase;
    for (char c : val) {
        if (std::isalnum(c)) {
            ss << std::setw(0) << c;
        } else {
            ss << "\\x" << std::setw(2) << (int)(unsigned char)c;
        }
    }
    ss << '"';

    return ss.str();
}

std::string to_hex(const ByteArray& val)
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::uppercase;
    for (char c : val) {
        ss << std::setw(2) << (int)(unsigned char)c;
    }
    return ss.str();
}

ByteArray to_bytes(const std::string& str)
{
    const char* start = str.data();
    return ByteArray(start, start + str.size());
}

bool to_bool(const std::string& str)
{
    return !str.empty();
}

}
