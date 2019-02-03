#include <stddef.h>
#include <string>
#include <sstream>

#include "stx/url.hpp"



namespace stx {

std::string urlquote(const std::string& str)
{
    std::stringstream ss;
    ss << std::hex << std::uppercase;
    for (char c : str) {
        if (std::isalnum(c) || c == '-' || c == '.' || c == '_' || c == '~') {
            ss << c;
        } else {
            ss << '%' << (int)(unsigned char)c;
        }
    }
    return ss.str();
}


Url::Url(const std::string& str)
{
    // TODO: better parser
    size_t scheme_end = str.find("://");
    scheme = str.substr(0, scheme_end);
    size_t netloc_start = scheme_end + 3;
    size_t netloc_end = str.find("/", netloc_start);
    netloc = str.substr(netloc_start, netloc_end - netloc_start);
    size_t path_start = netloc_end;
    size_t path_end = str.size();
    path = str.substr(path_start, path_end - path_start);
}

std::string Url::str() const
{
    std::stringstream ss;

    if (!scheme.empty()) {
        ss << scheme << "://" << netloc;
    } else if (!netloc.empty()) {
        ss << "//" << netloc;
    }
    ss << path;
    if (!params.empty()) {
        ss << ';' << params;
    }
    if (!query.empty()) {
        ss << '?' << query;
    }
    if (!fragment.empty()) {
        ss << '#' << fragment;
    }
    return ss.str();
}

void Url::addQuery(const std::string& name, const std::string& value)
{
    if (!query.empty()) {
        query += '&';
    }
    query += urlquote(name) + '=' + urlquote(value);
}

}
