#pragma once
#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <utility>

#include "bytearray.hpp"
#include "json.hpp"
#include "url.hpp"



namespace stx {

class HttpResponse;
class EasyCurl;

typedef std::pair<std::string,std::string> StringPair;


class RequestError : public std::runtime_error
{
public:
    explicit RequestError(std::string str);
};

class HttpError : public std::runtime_error
{
public:
    explicit HttpError(int status_);

    int status;
};


class HttpRequest
{
public:
    HttpRequest();
    HttpRequest(std::string url);
    HttpRequest(const stx::Url& url);

    std::string getUrl() const;
    void setUrl(std::string url);
    void setUrl(const stx::Url& url);
    std::string getHeader(const std::string& name) const;
    void setHeader(std::string name, std::string value);
    std::vector<StringPair> getQuery();
    void setQuery(std::vector<StringPair> query);
    void addQuery(std::string name, std::string value);
    ByteArray getPayload() const;
    void setPayload(ByteArray payload);
    bool getDoThrow() const;
    void setDoThrow(bool do_throw);

    HttpResponse request();

private:
    std::string m_url;
    std::map<std::string,std::string> m_headers;
    std::vector<std::pair<std::string,std::string>> m_query;
    ByteArray m_payload;
    bool m_do_throw;
};


class HttpResponse
{
public:
    HttpResponse() = default;
    HttpResponse(std::shared_ptr<EasyCurl> curl);

    ByteArray getData() const;
    ByteArray& getDataRef();
    stx::json getJson();
    int getStatus();
    int ok();
    void throwStatus();

private:
    std::shared_ptr<EasyCurl> m_curl;
    ByteArray m_data;
};

}
