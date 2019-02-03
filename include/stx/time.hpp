#pragma once
#include <time.h>
#include <stdint.h>
#include <cassert>



namespace stx {

class Timestamp
{
public:
    constexpr Timestamp(int64_t sec_) :
        sec(sec_),
        nsec(0)
    {
        assert(sec_ > 0);
    }

    constexpr Timestamp(int64_t sec_, int32_t nsec_) :
        sec(sec_),
        nsec(nsec_)
    {
        assert(sec_ > 0);
        assert(nsec_ >= 0 && nsec < 1000000000);
    }

    void operator+=(const Timestamp& rhs);
    Timestamp operator+(const Timestamp& rhs) const;
    void operator-=(const Timestamp& rhs);
    Timestamp operator-(const Timestamp& rhs) const;
    bool operator==(const Timestamp& rhs) const;
    bool operator!=(const Timestamp& rhs) const;
    bool operator<(const Timestamp& rhs) const;
    bool operator>(const Timestamp& rhs) const;
    bool operator<=(const Timestamp& rhs) const;
    bool operator>=(const Timestamp& rhs) const;

    double to_double() const;

    int64_t sec;
    int32_t nsec;
};

Timestamp get_timestamp(int source);

}
