#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>

#include "stx/conversion.hpp"
#include "stx/bytearray.hpp"



namespace stx {

namespace detail {

std::string to_repr(const std::string& val)
{
    std::stringstream ss;
    ss << '"';
    for (char c : val) {
        // TODO: replace isprint because it does not support UTF8
        if (!std::isprint(c)) {
            ss << "\\x" << stx::to_hex(c);
        } else if (c == '"') {
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

}

std::string to_hex(char val)
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::uppercase;
    ss << std::setw(2) << (int)(unsigned char)val;
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

bool to_bool(const std::string& str)
{
    return !str.empty();
}

}
