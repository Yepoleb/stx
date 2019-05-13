#include <stdint.h>
#include <cassert>
#include <cstdio>

#include "stx/memorystream.hpp"
#include "stx/stream.hpp"
#include "stx/bytearray.hpp"
#include "stx/exception.hpp"
#include "stx/algorithm.hpp"



namespace stx {

MemoryStream::MemoryStream()
{
    m_buffer = nullptr;
    m_pos = 0;
}

MemoryStream::MemoryStream(ByteArray& buffer)
{
    m_buffer = &buffer;
    m_pos = 0;
}

int64_t MemoryStream::readInto1(void* buffer, int64_t size)
{
    int64_t remaining = m_buffer->size() - m_pos;
    int64_t maxread = stx::constrain_max(remaining, size);
    assert(maxread >= 0);
    std::memcpy(buffer, m_buffer->data() + m_pos, maxread);
    m_pos += maxread;

    return maxread;
}

int64_t MemoryStream::write1(const void* buffer, int64_t size)
{
    int64_t bufsize_req = m_pos + size;
    if (bufsize_req > (int64_t)m_buffer->size()) {
        m_buffer->resize(bufsize_req);
    }
    assert(size >= 0);
    std::memcpy(m_buffer->data() + m_pos, buffer, size);
    m_pos += size;

    return size;
}

int64_t MemoryStream::tell()
{
    return m_pos;
}

void MemoryStream::seek(int64_t offset, int origin)
{
    if (origin == SEEK_SET) {
        m_pos = offset;
    } else if (origin == SEEK_END) {
        m_pos = m_buffer->size() - offset;
    } else if (origin == SEEK_CUR) {
        m_pos += offset;
    } else {
        throw NotImplementedError();
    }
    assert(m_pos <= (int64_t)m_buffer->size());
}

bool MemoryStream::seekable() const
{
    return true;
}



ConstMemoryStream::ConstMemoryStream()
{
    m_buffer = nullptr;
    m_size = 0;
    m_pos = 0;
}

ConstMemoryStream::ConstMemoryStream(const ByteArray& buffer)
{
    m_buffer = buffer.data();
    m_size = buffer.size();
    m_pos = 0;
}

ConstMemoryStream::ConstMemoryStream(const void* buffer, int64_t size)
{
    m_buffer = reinterpret_cast<const char*>(buffer);
    m_size = size;
    m_pos = 0;
}

int64_t ConstMemoryStream::readInto1(void* buffer, int64_t size)
{
    int64_t remaining = m_size - m_pos;
    int64_t maxread = stx::constrain_max(remaining, size);
    assert(maxread >= 0);
    std::memcpy(buffer, m_buffer + m_pos, maxread);
    m_pos += maxread;

    return maxread;
}

int64_t ConstMemoryStream::write1(
    [[maybe_unused]] const void* buffer, [[maybe_unused]] int64_t size)
{
    throw NotImplementedError();
}

int64_t ConstMemoryStream::tell()
{
    return m_pos;
}

void ConstMemoryStream::seek(int64_t offset, int origin)
{
    if (origin == SEEK_SET) {
        m_pos = offset;
    } else if (origin == SEEK_END) {
        m_pos = m_size - offset;
    } else if (origin == SEEK_CUR) {
        m_pos += offset;
    } else {
        throw NotImplementedError();
    }
    assert(m_pos <= m_size);
}

bool ConstMemoryStream::seekable() const
{
    return true;
}

}
