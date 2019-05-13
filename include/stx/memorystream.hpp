#pragma once
#include <stdint.h>

#include "stx/stream.hpp"
#include "stx/bytearray.hpp"



namespace stx {

class MemoryStream : public BaseStream
{
public:
    MemoryStream();
    MemoryStream(ByteArray& buffer);

    int64_t readInto1(void* buffer, int64_t size) override;
    int64_t write1(const void* buffer, int64_t size) override;

    int64_t tell() override;
    void seek(int64_t offset, int origin) override;
    bool seekable() const override;

private:
    ByteArray* m_buffer;
    int64_t m_pos;
};

// TODO: MemoryStream with own buffer
// TODO: StringStream

class ConstMemoryStream : public BaseStream
{
public:
    ConstMemoryStream();
    ConstMemoryStream(const ByteArray& buffer);
    ConstMemoryStream(const void* buffer, int64_t size);

    int64_t readInto1(void* buffer, int64_t size) override;
    int64_t write1(const void* buffer, int64_t size) override;

    int64_t tell() override;
    void seek(int64_t offset, int origin) override;
    bool seekable() const override;

private:
    const char* m_buffer;
    int64_t m_size;
    int64_t m_pos;
};

}
