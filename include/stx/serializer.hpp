#pragma once
#include <stdint.h>

#include "stx/stream.hpp"



namespace stx {

class BaseSerializer
{
public:
    constexpr BaseSerializer() : m_stream(nullptr) {}
    constexpr BaseSerializer(BaseStream* stream) : m_stream(stream) {}
    constexpr BaseSerializer(BaseStream& stream) : m_stream(&stream) {}
    void flush();
    int64_t tell();
    void seek(int64_t offset, int origin);
    bool seekable() const;

    BaseStream* getStream();
    void setStream(BaseStream* stream);

protected:
    BaseStream* m_stream;
};

}
