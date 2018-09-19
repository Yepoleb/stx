#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <vector>

#include "bytearray.hpp"



namespace stx {

bool startswith(char c, const std::string& str)
{
    if (str.empty()) {
        return false;
    }
    return str.front() == c;
}

bool startswith(const std::string& start, const std::string& str)
{
    return start == str.substr(0, start.size());
}

bool endswith(char c, const std::string& str)
{
    if (str.empty()) {
        return false;
    }
    return str.back() == c;
}

bool endswith(const std::string& end, const std::string& str)
{
    if (str.size() < end.size()) {
        return false;
    }
    return end == str.substr(str.size() - end.size(), end.size());
}

std::tm parseDate(std::string input, const std::string& fmt)
{
    std::tm tmp;
    std::stringstream ss(input);
    ss >> std::get_time(&tmp, fmt.c_str());

    return tmp;
}

std::string formatDate(std::tm date, const std::string& fmt)
{
    std::stringstream ss;
    ss << std::put_time(&date, fmt.c_str());
    return ss.str();
}

std::vector<std::string> split(const std::string& src, std::string sep, int maxsplit)
{
    std::vector<std::string> out;
    size_t found = 0;
    size_t lastfound = 0;
    bool skip_empty = false;
    if (sep == "") {
        sep = " ";
        skip_empty = true;
    }
    if (maxsplit < 0) {
        maxsplit = std::numeric_limits<int>::max();
    }

    bool loop = true;
    while (loop) {
        found = src.find(sep, lastfound);
        std::string sub;
        if (found == std::string::npos or (int)out.size() + 1 >= maxsplit) {
            sub = src.substr(lastfound, src.size());
            loop = false;
        } else {
            sub = src.substr(lastfound, found-lastfound);
        }

        lastfound = found + sep.size();
        if (skip_empty and sub.empty())
            continue;

        out.push_back(sub);
    }
    return out;
}

}
