#include <stddef.h>
#include <memory>
#include <sstream>
#include <cctype>
#include <cassert>

#include "curl/curl.h"

#include "stx/request.hpp"
#include "stx/json.hpp"
#include "stx/curl.hpp"
#include "stx/memorystream.hpp"



namespace stx {

RequestError::RequestError(std::string str) :
    std::runtime_error(str)
{

}


static std::string http_errorstr(int status)
{
    std::stringstream ss;
    ss << "HTTP error: " << status;
    return ss.str();
}

HttpError::HttpError(int status_) :
    std::runtime_error(http_errorstr(status_)),
    status(status_)
{

}


HttpRequest::HttpRequest()
{
    m_do_throw = false;
}
HttpRequest::HttpRequest(std::string url) :
    HttpRequest()
{
    setUrl(url);
}
HttpRequest::HttpRequest(const stx::Url& url) :
    HttpRequest()
{
    setUrl(url);
}

std::string HttpRequest::getUrl() const
{
    return m_url;
}
void HttpRequest::setUrl(std::string url)
{
    m_url = url;
}
void HttpRequest::setUrl(const stx::Url& url)
{
    m_url = url.str();
}
std::string HttpRequest::getHeader(const std::string& name) const
{
    return m_headers.at(name);
}
void HttpRequest::setHeader(std::string name, std::string value)
{
    m_headers[name] = value;
}
std::vector<StringPair> HttpRequest::getQuery()
{
    return m_query;
}
void HttpRequest::setQuery(std::vector<StringPair> query)
{
    m_query = query;
}
void HttpRequest::addQuery(std::string name, std::string value)
{
    m_query.push_back({name, value});
}
ByteArray HttpRequest::getPayload() const
{
    return m_payload;
}
void HttpRequest::setPayload(ByteArray payload)
{
    m_payload = payload;
}
bool HttpRequest::getDoThrow() const
{
    return m_do_throw;
}
void HttpRequest::setDoThrow(bool do_throw)
{
    m_do_throw = do_throw;
}



static size_t curlWriteCb(char* content, size_t size, size_t nmemb, void* userdata)
{
    size_t nbytes = size * nmemb;

    MemoryStream* stream = reinterpret_cast<MemoryStream*>(userdata);
    return stream->write(content, nbytes);
}

static size_t curlReadCb(char* content, size_t size, size_t nmemb, void* userdata)
{
    size_t nbytes = size * nmemb;

    MemoryStream* stream = reinterpret_cast<MemoryStream*>(userdata);
    return stream->readInto(content, nbytes);
}

HttpResponse HttpRequest::request()
{
    auto curl = std::make_shared<EasyCurl>();

    assert(!m_url.empty());
    curl->setopt(CURLOPT_URL, m_url.data());

    CurlSList headers_slist;
    for (std::pair<std::string,std::string> header_entry : m_headers) {
        headers_slist.append(header_entry.first + ": " + header_entry.second);
    }
    curl->setopt(CURLOPT_HTTPHEADER, headers_slist.ptr());

    MemoryStream read_stream(m_payload);
    if (!m_payload.empty()) {
        curl->setopt(CURLOPT_POST, 1);
        curl->setopt(CURLOPT_READFUNCTION, reinterpret_cast<void*>(curlReadCb));
        curl->setopt(CURLOPT_READDATA, &read_stream);
        curl->setopt(CURLOPT_POSTFIELDSIZE, m_payload.size());
    }

    HttpResponse resp(curl);
    curl->setopt(CURLOPT_WRITEFUNCTION, reinterpret_cast<void*>(curlWriteCb));
    MemoryStream write_stream(resp.getDataRef());
    curl->setopt(CURLOPT_WRITEDATA, &write_stream);

    curl->perform();

    if (m_do_throw) {
        resp.throwStatus();
    }

    return resp;
}



HttpResponse::HttpResponse(std::shared_ptr<EasyCurl> curl)
{
    m_curl = curl;
}

ByteArray HttpResponse::getData() const
{
    return m_data;
}

ByteArray& HttpResponse::getDataRef()
{
    return m_data;
}

stx::json HttpResponse::getJson()
{
    return stx::json::parse(m_data);
}

int HttpResponse::getStatus()
{
    long status;
    m_curl->getinfo(CURLINFO_RESPONSE_CODE, &status);
    return static_cast<int>(status);
}

bool HttpResponse::ok()
{
    return getStatus() < 400;
}

void HttpResponse::throwStatus()
{
    int status = getStatus();
    if (status >= 400) {
        throw HttpError(status);
    }
}

}
