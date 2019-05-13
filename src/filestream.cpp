#include <stdint.h>
#include <cassert>
#include <system_error>
#include <cstdio>

#include "stx/filestream.hpp"
#include "stx/stream.hpp"



namespace stx {

std::FILE* RawFileStream::getFilePointer()
{
    return m_file;
}

void RawFileStream::setFilePointer(std::FILE* fp)
{
    m_file = fp;
}

int64_t RawFileStream::readInto1(void* buffer, int64_t size)
{
    assert(m_file);
    int64_t bytes_read = std::fread(buffer, 1, size, m_file);
    if (ferror(m_file)) {
        throw std::system_error(errno, std::system_category());
    }
    return bytes_read;
}

int64_t RawFileStream::write1(const void* buffer, int64_t size)
{
    assert(m_file);
    int64_t bytes_written = std::fwrite(buffer, 1, size, m_file);
    if (ferror(m_file)) {
        throw std::system_error(errno, std::system_category());
    }
    return bytes_written;
}

void RawFileStream::flush()
{
    assert(m_file);
    if (std::fflush(m_file)) {
        throw std::system_error(errno, std::system_category());
    }
}



FileStream::FileStream(const char* path, const char* mode)
{
    m_file = nullptr;
    m_isopen = false;
    open(path, mode);
}

FileStream::FileStream(const std::string& path, const std::string& mode)
{
    m_file = nullptr;
    m_isopen = false;
    open(path, mode);
}

FileStream::FileStream(FileStream&& other)
{
    close();
    m_file = other.m_file;
    m_isopen = other.m_isopen;
    other.m_file = nullptr;
}

FileStream& FileStream::operator=(FileStream&& other)
{
    close();
    m_file = other.m_file;
    m_isopen = other.m_isopen;
    other.m_file = nullptr;
    return *this;
}

FileStream::~FileStream()
{
    close();
}

void FileStream::open(const char* path, const char* mode)
{
    close();
    m_file = std::fopen(path, mode);
    if (!m_file) {
        m_isopen = false;
        throw std::system_error(errno, std::system_category());
    }
    m_isopen = true;
}

void FileStream::open(const std::string& path, const std::string& mode)
{
    open(path.c_str(), mode.c_str());
}

void FileStream::close()
{
    if (!m_file || !m_isopen) return;
    m_isopen = false;
    if (std::fclose(m_file)) {
        throw std::system_error(errno, std::system_category());
    }
}

bool FileStream::isOpen() const
{
    return m_isopen;
}

int64_t FileStream::tell()
{
    assert(m_file);
    int64_t offset = std::ftell(m_file);
    if (offset == -1l) {
        throw std::system_error(errno, std::system_category());
    }
    return offset;
}

void FileStream::seek(int64_t offset, int origin)
{
    assert(m_file);
    if (std::fseek(m_file, offset, origin)) {
        throw std::system_error(errno, std::system_category());
    }
}

bool FileStream::seekable() const
{
    return true;
}

}
