#pragma once
#include <stdint.h>
#include <string>
#include <cstdio>

#include "stream.hpp"
#include "bytearray.hpp"



namespace stx {

class RawFileStream : public BaseStream
{
public:
    constexpr RawFileStream() :
        m_file(nullptr)
    {

    }

    constexpr RawFileStream(std::FILE* fp) :
        m_file(fp)
    {

    }

    std::FILE* getFilePointer();
    void setFilePointer(std::FILE* fp);

    int64_t readInto1(char* buffer, int64_t size) override;
    int64_t write1(const char* buffer, int64_t size) override;
    void flush() override;

protected:
    std::FILE* m_file;
};

class FileStream : public RawFileStream
{
public:
    FileStream(const char* path, const char* mode);
    FileStream(const std::string& path, const std::string& mode);
    FileStream(const FileStream& other) = delete;
    FileStream(FileStream&& other);
    FileStream& operator=(const FileStream& other) = delete;
    FileStream& operator=(FileStream&& other);
    ~FileStream();

    void open(const char* path, const char* mode);
    void open(const std::string& path, const std::string& mode);
    void close();
    bool isOpen() const;

    int64_t tell() override;
    void seek(int64_t offset, int origin) override;
    bool seekable() const override;

protected:
    // Make setFilePointer protected because keeping it public would cause
    // a lot of ownership issues
    using RawFileStream::setFilePointer;

private:
    bool m_isopen;
};

// Can be constexpr constructed, so they shouldn't impact startup time
static RawFileStream sout(stdout);
static RawFileStream sin(stdin);
static RawFileStream serr(stderr);

}
