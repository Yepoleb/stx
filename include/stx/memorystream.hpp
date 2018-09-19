#include <stdint.h>

#include "stream.hpp"
#include "bytearray.hpp"



namespace stx {

class MemoryStream : public BaseStream
{
public:
    MemoryStream();
    MemoryStream(ByteArray& buffer);

    int64_t readInto1(char* buffer, int64_t size) override;
    int64_t write1(const char* buffer, int64_t size) override;

    int64_t tell() override;
    void seek(int64_t offset, int origin) override;
    bool seekable() const override;

private:
    ByteArray* m_buffer;
    int64_t m_pos;
};

}
