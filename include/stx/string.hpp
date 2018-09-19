#pragma once
#include <string>
#include <sstream>
#include <ctime>
#include <vector>

#include "bytearray.hpp"
#include "conversion.hpp"
#include "textserializer.hpp"
#include "memorystream.hpp"



namespace stx {

template<typename... Targs>
std::string format(Targs... args)
{
    stx::ByteArray buffer;
    stx::MemoryStream mems(buffer);
    stx::TextSerializer ser(mems);
    ser.printf(args...);
    return stx::to_str(buffer);
}

bool startswith(char c, const std::string& str);
bool startswith(const std::string& start, const std::string& str);
bool endswith(char c, const std::string& str);
bool endswith(const std::string& end, const std::string& str);
std::tm parseDate(std::string input, const std::string& fmt);
std::string formatDate(std::tm date, const std::string& fmt);
std::vector<std::string> split(const std::string& src, std::string sep=std::string(), int maxsplit=-1);

}
