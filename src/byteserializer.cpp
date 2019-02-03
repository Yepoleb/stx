#include <stdint.h>
#include <string>
#include <vector>
#include <cassert>

#include "stx/byteserializer.hpp"
#include "stx/stream.hpp"
#include "stx/bytearray.hpp"
#include "stx/integer.hpp"


namespace stx {

static const int64_t PAD_CHUNKSIZE = 16;
static const char PAD_ZEROS[PAD_CHUNKSIZE] = {0};



ByteSerializer::ByteSerializer(stx::BaseStream& stream_) :
    stream(stream_)
{

}

ByteArray ByteSerializer::read(int64_t size)
{
    return stream.read(size);
}

int64_t ByteSerializer::write(const ByteArray& buffer)
{
    return stream.write(buffer);
}



void ByteSerializer::ignore(int64_t size)
{
    stream.seek(size, SEEK_CUR);
}

void ByteSerializer::align(int64_t alignment)
{
    int64_t current_pos = stream.tell();
    int64_t to_align = current_pos % alignment;
    if (to_align > 0) {
        ignore(to_align);
    }
}

void ByteSerializer::pad(int64_t size)
{
    while (size >= PAD_CHUNKSIZE) {
        stream.write(PAD_ZEROS, PAD_CHUNKSIZE);
        size -= PAD_CHUNKSIZE;
    }
    if (size) {
        assert(size < PAD_CHUNKSIZE);
        stream.write(PAD_ZEROS, size);
    }
}

void ByteSerializer::padAlign(int64_t alignment)
{
    std::streampos current_pos = stream.tell();
    std::streamoff to_align = current_pos % alignment;
    pad(to_align);
}



std::string ByteSerializer::readString(int64_t n)
{
    std::string str(n, 0);
    stream.readInto(str.data(), n);
    return str;
}

std::string ByteSerializer::readCString(char delim)
{
    std::string str;
    while (true) {
        char c = readChar();
        if (c == delim) {
            break;
        }
        str.push_back(c);
    }
    return str;
}

void ByteSerializer::writeString(const std::string& str)
{
    stream.write(str.data(), str.size());
}

void ByteSerializer::writeCString(const std::string& str)
{
    stream.write(str.c_str(), str.size() + 1);
}



int64_t ByteSerializer::readS64NA()
{
    return read_generic<int64_t>();
}

int32_t ByteSerializer::readS32NA()
{
    return read_generic<int32_t>();
}

int16_t ByteSerializer::readS16NA()
{
    return read_generic<int16_t>();
}

uint64_t ByteSerializer::readU64NA()
{
    return read_generic<uint64_t>();
}

uint32_t ByteSerializer::readU32NA()
{
    return read_generic<uint32_t>();
}

uint16_t ByteSerializer::readU16NA()
{
    return read_generic<uint16_t>();
}

int64_t ByteSerializer::readS64BE()
{
    return stx::swap_be_u64(read_generic<int64_t>());
}

int32_t ByteSerializer::readS32BE()
{
    return stx::swap_be_u32(read_generic<int32_t>());
}

int16_t ByteSerializer::readS16BE()
{
    return stx::swap_be_u16(read_generic<int16_t>());
}

uint64_t ByteSerializer::readU64BE()
{
    return stx::swap_be_u64(read_generic<uint64_t>());
}

uint32_t ByteSerializer::readU32BE()
{
    return stx::swap_be_u32(read_generic<uint32_t>());
}

uint16_t ByteSerializer::readU16BE()
{
    return stx::swap_be_u16(read_generic<uint16_t>());
}

int64_t ByteSerializer::readS64LE()
{
    return stx::swap_le_u64(read_generic<int64_t>());
}

int32_t ByteSerializer::readS32LE()
{
    return stx::swap_le_u32(read_generic<int32_t>());
}

int16_t ByteSerializer::readS16LE()
{
    return stx::swap_le_u16(read_generic<int16_t>());
}

uint64_t ByteSerializer::readU64LE()
{
    return stx::swap_le_u64(read_generic<uint64_t>());
}

uint32_t ByteSerializer::readU32LE()
{
    return stx::swap_le_u32(read_generic<uint32_t>());
}

uint16_t ByteSerializer::readU16LE()
{
    return stx::swap_le_u16(read_generic<uint16_t>());
}

int8_t ByteSerializer::readS8()
{
    return read_generic<int8_t>();
}

uint8_t ByteSerializer::readU8()
{
    return read_generic<uint8_t>();
}

char ByteSerializer::readChar()
{
    return read_generic<char>();
}

unsigned char ByteSerializer::readUChar()
{
    return read_generic<unsigned char>();
}

bool ByteSerializer::readBool()
{
    return read_generic<bool>();
}

float ByteSerializer::readFloat()
{
    return read_generic<float>();
}

double ByteSerializer::readDouble()
{
    return read_generic<double>();
}



void ByteSerializer::writeS64NA(int64_t value)
{
    write_generic<int64_t>(value);
}

void ByteSerializer::writeS32NA(int32_t value)
{
    write_generic<int32_t>(value);
}

void ByteSerializer::writeS16NA(int16_t value)
{
    write_generic<int16_t>(value);
}

void ByteSerializer::writeU64NA(uint64_t value)
{
    write_generic<uint64_t>(value);
}

void ByteSerializer::writeU32NA(uint32_t value)
{
    write_generic<uint32_t>(value);
}

void ByteSerializer::writeU16NA(uint16_t value)
{
    write_generic<uint16_t>(value);
}

void ByteSerializer::writeS64BE(int64_t value)
{
    write_generic<int64_t>(stx::swap_be_u64(value));
}

void ByteSerializer::writeS32BE(int32_t value)
{
    write_generic<int32_t>(stx::swap_be_u32(value));
}

void ByteSerializer::writeS16BE(int16_t value)
{
    write_generic<int16_t>(stx::swap_be_u16(value));
}

void ByteSerializer::writeU64BE(uint64_t value)
{
    write_generic<uint64_t>(stx::swap_be_u64(value));
}

void ByteSerializer::writeU32BE(uint32_t value)
{
    write_generic<uint32_t>(stx::swap_be_u32(value));
}

void ByteSerializer::writeU16BE(uint16_t value)
{
    write_generic<uint16_t>(stx::swap_be_u16(value));
}

void ByteSerializer::writeS64LE(int64_t value)
{
    write_generic<int64_t>(stx::swap_le_u64(value));
}

void ByteSerializer::writeS32LE(int32_t value)
{
    write_generic<int32_t>(stx::swap_le_u32(value));
}

void ByteSerializer::writeS16LE(int16_t value)
{
    write_generic<int16_t>(stx::swap_le_u16(value));
}

void ByteSerializer::writeU64LE(uint64_t value)
{
    write_generic<uint64_t>(stx::swap_le_u64(value));
}

void ByteSerializer::writeU32LE(uint32_t value)
{
    write_generic<uint32_t>(stx::swap_le_u32(value));
}

void ByteSerializer::writeU16LE(uint16_t value)
{
    write_generic<uint16_t>(stx::swap_le_u16(value));
}

void ByteSerializer::writeS8(int8_t value)
{
    write_generic<int8_t>(value);
}

void ByteSerializer::writeU8(uint8_t value)
{
    write_generic<uint8_t>(value);
}

void ByteSerializer::writeChar(char value)
{
    write_generic<char>(value);
}

void ByteSerializer::writeUChar(unsigned char value)
{
    write_generic<unsigned char>(value);
}

void ByteSerializer::writeBool(bool value)
{
    write_generic<bool>(value);
}

void ByteSerializer::writeFloat(float value)
{
    write_generic<float>(value);
}

void ByteSerializer::writeDouble(double value)
{
    write_generic<double>(value);
}

}
