#include <stdint.h>
#include <cassert>
#include <cstdio>

#include "memorystream.hpp"
#include "stream.hpp"
#include "bytearray.hpp"



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

int64_t MemoryStream::readInto1(char* buffer, int64_t size)
{
    int64_t remaining = m_buffer->size() - m_pos;
    int64_t maxread = std::min(remaining, size);
    assert(maxread >= 0);
    std::memcpy(buffer, m_buffer->data() + m_pos, maxread);
    m_pos += maxread;

    return maxread;
}

int64_t MemoryStream::write1(const char* buffer, int64_t size)
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
    } else { // SEEK_CUR
        m_pos += offset;
    }
}

bool MemoryStream::seekable() const
{
    return true;
}

}
