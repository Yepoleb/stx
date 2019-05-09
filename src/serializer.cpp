#include <stdint.h>
#include <assert.h>

#include "stx/serializer.hpp"



namespace stx {

void BaseSerializer::flush()
{
    assert(m_stream != nullptr);
    m_stream->flush();
}

int64_t BaseSerializer::tell()
{
    assert(m_stream != nullptr);
    return m_stream->tell();
}

void BaseSerializer::seek(int64_t offset, int origin)
{
    assert(m_stream != nullptr);
    m_stream->seek(offset, origin);
}

bool BaseSerializer::seekable() const
{
    assert(m_stream != nullptr);
    return m_stream->seekable();
}

BaseStream* BaseSerializer::getStream()
{
    return m_stream;
}

void BaseSerializer::setStream(BaseStream* stream)
{
    m_stream = stream;
}

}
