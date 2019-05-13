#include <stdint.h>
#include <algorithm>
#include <limits>

#include "stx/stream.hpp"
#include "stx/exception.hpp"
#include "stx/algorithm.hpp"



namespace stx {

void BaseStream::flush()
{
    return;
}

int64_t BaseStream::tell()
{
    throw NotImplementedError();
}

void BaseStream::seek([[maybe_unused]] int64_t offset, [[maybe_unused]] int origin)
{
    throw NotImplementedError();
}

bool BaseStream::seekable() const
{
    return false;
}

int64_t BaseStream::readInto(void* buffer, int64_t size)
{
    int64_t pos = 0;

    while (pos < size) {
        int64_t to_read = size - pos;
        int64_t bytes_read = readInto1(
            reinterpret_cast<char*>(buffer) + pos, to_read);

        if (bytes_read == 0) {
            break;
        }

        pos += bytes_read;
    }
    return pos;
}

int64_t BaseStream::write(const void* buffer, int64_t size)
{
    int64_t pos = 0;

    while (pos < size) {
        int64_t to_write = size - pos;
        int64_t bytes_written = write1(
            reinterpret_cast<const char*>(buffer) + pos, to_write);

        if (bytes_written == 0) {
            break;
        }

        pos += bytes_written;
    }
    return pos;
}

ByteArray BaseStream::read1(int64_t size)
{
    ByteArray buffer(size);
    int64_t actual_size = readInto1(buffer.data(), size);
    buffer.resize(actual_size);
    return buffer;
}

ByteArray BaseStream::read(int64_t size)
{
    ByteArray read_buffer(BUFSIZ);
    ByteArray data_buffer;
    int64_t remaining = size != -1 ? size : INT64_MAX;

    while (remaining) {
        int64_t to_read = stx::constrain_max(remaining, (int64_t)BUFSIZ);
        int64_t bytes_read = readInto1(read_buffer.data(), to_read);

        if (bytes_read == 0) {
            break;
        }

        stx::append(data_buffer, read_buffer.data(), bytes_read);
        remaining -= bytes_read;
    }
    return data_buffer;
}

int64_t BaseStream::write(const ByteArray& buffer)
{
    return write(buffer.data(), buffer.size());
}

}
