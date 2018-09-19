#include <string>
#include <cassert>
#include <stdint.h>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <cstring>

#include "textserializer.hpp"
#include "stream.hpp"
#include "bytearray.hpp"



namespace stx {

void TextSerializer::write(const std::string& str)
{
    assert(stream);
    stream->write(str.data(), str.size());
}

void TextSerializer::write(const char* str)
{
    assert(stream);
    stream->write(str, std::strlen(str));
}

void TextSerializer::print(const std::string& str)
{
    write(str);
}

void TextSerializer::print(const char* str)
{
    write(str);
}

std::string TextSerializer::read(int64_t size)
{
    assert(stream);
    ByteArray ba = stream->read(size);
    return stx::to_str(ba);
}

std::string TextSerializer::readUntil(char sep, int64_t size)
{
    assert(stream);

    if (size < 0) {
        size = std::numeric_limits<int64_t>::max();
    }

    ByteArray ba;
    while ((int64_t)ba.size() < size) {
        char c;
        int64_t size_read = stream->readInto1(&c, 1);
        if (!size_read) {
            break;
        }
        if (c == sep) {
            break;
        } else {
            ba.push_back(c);
        }
    }
    return stx::to_str(ba);
}

std::string TextSerializer::readLine(int64_t size)
{
    return readUntil('\n', size);
}



BaseStream* TextSerializer::getStream()
{
    return stream;
}

}
