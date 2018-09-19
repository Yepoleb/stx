#pragma once
#include "curl/curl.h"


namespace stx {

class CurlError : public std::runtime_error
{
public:
    explicit CurlError(CURLcode code_);

    CURLcode code;
};



class EasyCurl
{
public:
    EasyCurl();
    EasyCurl(const EasyCurl& other) = delete;
    EasyCurl& operator=(const EasyCurl& other) = delete;
    EasyCurl(EasyCurl&& other);
    ~EasyCurl();

    void setopt(CURLoption option, void* parameter);
    void setopt(CURLoption option, long parameter);
    void getinfo(CURLINFO info, void* parameter);
    void perform();

private:
    CURL* m_curl;
};


class CurlSList
{
public:
    CurlSList();
    CurlSList(const CurlSList& other) = delete;
    CurlSList& operator=(const CurlSList& other) = delete;
    CurlSList(CurlSList&& other);
    ~CurlSList();
    curl_slist* ptr();
    const curl_slist* ptr() const;

    void append(const std::string& str);
    void append(const char* str);

private:
    curl_slist* m_slist;
};

}
