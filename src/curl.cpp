#include <string>
#include <sstream>
#include <stdexcept>

#include "curl/curl.h"

#include "stx/curl.hpp"



namespace stx {

static std::string curl_errorstr(CURLcode code)
{
    std::stringstream ss;
    ss << "CURL error (" << code << "): " << curl_easy_strerror(code);

    return ss.str();
}

CurlError::CurlError(CURLcode code_) :
    std::runtime_error(curl_errorstr(code_)),
    code(code_)
{

}



EasyCurl::EasyCurl()
{
    m_curl = curl_easy_init();
    if (!m_curl) {
        throw std::bad_alloc();
    }
}
EasyCurl::EasyCurl(EasyCurl&& other)
{
    m_curl = other.m_curl;
    other.m_curl = nullptr;
}
EasyCurl::~EasyCurl()
{
    curl_easy_cleanup(m_curl);
}

void EasyCurl::setopt(CURLoption option, void* parameter)
{
    CURLcode code = curl_easy_setopt(m_curl, option, parameter);
    if (code != CURLE_OK) {
        throw CurlError(code);
    }
}

void EasyCurl::setopt(CURLoption option, long parameter)
{
    CURLcode code = curl_easy_setopt(m_curl, option, parameter);
    if (code != CURLE_OK) {
        throw CurlError(code);
    }
}

void EasyCurl::getinfo(CURLINFO info, void* parameter)
{
    CURLcode code = curl_easy_getinfo(m_curl, info, parameter);
    if (code != CURLE_OK) {
        throw CurlError(code);
    }
}

void EasyCurl::perform()
{
    CURLcode code = curl_easy_perform(m_curl);
    if (code != CURLE_OK) {
        throw CurlError(code);
    }
}



CurlSList::CurlSList()
{
    m_slist = nullptr;
}
CurlSList::CurlSList(CurlSList&& other)
{
    m_slist = other.m_slist;
    other.m_slist = nullptr;
}
CurlSList::~CurlSList()
{
    curl_slist_free_all(m_slist);
}
curl_slist* CurlSList::ptr()
{
    return m_slist;
}
const curl_slist* CurlSList::ptr() const
{
    return m_slist;
}

void CurlSList::append(const std::string& str)
{
    m_slist = curl_slist_append(m_slist, str.data());
}
void CurlSList::append(const char* str)
{
    m_slist = curl_slist_append(m_slist, str);
}

}
