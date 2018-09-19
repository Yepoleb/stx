#pragma once
#include <string>



namespace stx {

std::string urlquote(const std::string& str);

class Url
{
public:
    Url();
    Url(const std::string& str);

    std::string str() const;
    void addQuery(const std::string& name, const std::string& value);

    std::string scheme;
    std::string netloc;
    std::string path;
    std::string params;
    std::string query;
    std::string fragment;
};

}
