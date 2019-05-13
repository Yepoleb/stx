#pragma once
#include <stdint.h>

#include "stx/bytearray.hpp"



namespace stx {

class BaseStream
{
public:
    virtual ~BaseStream() = default;

    virtual int64_t readInto1(void* buffer, int64_t size) = 0;
    virtual int64_t write1(const void* buffer, int64_t size) = 0;

    virtual void flush();
    virtual int64_t tell();
    virtual void seek(int64_t offset, int origin);
    virtual bool seekable() const;

    virtual int64_t readInto(void* buffer, int64_t size);
    virtual int64_t write(const void* buffer, int64_t size);
    virtual ByteArray read1(int64_t size);
    virtual ByteArray read(int64_t size);
    virtual int64_t write(const ByteArray& buffer);
};

}
