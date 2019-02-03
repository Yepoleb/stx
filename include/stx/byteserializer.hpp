#pragma once
#include <stdint.h>
#include <string>

#include "stx/bytearray.hpp"
#include "stx/stream.hpp"



namespace stx {

class BaseStream;

class ByteSerializer {
public:
    explicit ByteSerializer(stx::BaseStream& stream_);
    ByteArray read(int64_t size);
    int64_t write(const ByteArray& buffer);
    void ignore(int64_t size);
    void align(int64_t alignment);
    void pad(int64_t size);
    void padAlign(int64_t alignment);
    std::string readString(int64_t n);
    std::string readCString(char delim);
    void writeString(const std::string& str);
    void writeCString(const std::string& str);

    template<typename T>
    T read_generic()
    {
        T value;
        stream.readInto(reinterpret_cast<char*>(&value), sizeof(T));
        return value;
    }

    template<typename T>
    void write_generic(T value)
    {
        stream.write(reinterpret_cast<char*>(&value), sizeof(T));
    }

    int64_t readS64NA();
    int32_t readS32NA();
    int16_t readS16NA();
    uint64_t readU64NA();
    uint32_t readU32NA();
    uint16_t readU16NA();
    int64_t readS64BE();
    int32_t readS32BE();
    int16_t readS16BE();
    uint64_t readU64BE();
    uint32_t readU32BE();
    uint16_t readU16BE();
    int64_t readS64LE();
    int32_t readS32LE();
    int16_t readS16LE();
    uint64_t readU64LE();
    uint32_t readU32LE();
    uint16_t readU16LE();
    int8_t readS8();
    uint8_t readU8();
    char readChar();
    unsigned char readUChar();
    bool readBool();
    float readFloat();
    double readDouble();

    void writeS64NA(int64_t value);
    void writeS32NA(int32_t value);
    void writeS16NA(int16_t value);
    void writeU64NA(uint64_t value);
    void writeU32NA(uint32_t value);
    void writeU16NA(uint16_t value);
    void writeS64BE(int64_t value);
    void writeS32BE(int32_t value);
    void writeS16BE(int16_t value);
    void writeU64BE(uint64_t value);
    void writeU32BE(uint32_t value);
    void writeU16BE(uint16_t value);
    void writeS64LE(int64_t value);
    void writeS32LE(int32_t value);
    void writeS16LE(int16_t value);
    void writeU64LE(uint64_t value);
    void writeU32LE(uint32_t value);
    void writeU16LE(uint16_t value);
    void writeS8(int8_t value);
    void writeU8(uint8_t value);
    void writeChar(char value);
    void writeUChar(unsigned char value);
    void writeBool(bool value);
    void writeFloat(float value);
    void writeDouble(double value);

protected:
    stx::BaseStream& stream;
};

}
