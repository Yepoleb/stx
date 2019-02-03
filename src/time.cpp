#include <time.h>
#include <stdint.h>
#include <cassert>

#include "stx/time.hpp"



namespace stx {

void Timestamp::operator+=(const Timestamp& rhs)
{
    sec += rhs.sec;
    nsec += rhs.nsec;
    if (nsec >= 1000000000) {
        nsec -= 1000000000;
        sec += 1;
    }
}

Timestamp Timestamp::operator+(const Timestamp& rhs) const
{
    Timestamp ts(*this);
    ts += rhs;
    return ts;
}

void Timestamp::operator-=(const Timestamp& rhs)
{
    sec -= rhs.sec;
    nsec -= rhs.nsec;
    if (nsec < 0) {
        nsec += 1000000000;
        sec -= 1;
    }
}

Timestamp Timestamp::operator-(const Timestamp& rhs) const
{
    Timestamp ts(*this);
    ts -= rhs;
    return ts;
}

bool Timestamp::operator==(const Timestamp& rhs) const
{
    return (sec == rhs.sec) && (nsec == rhs.nsec);
}

bool Timestamp::operator!=(const Timestamp& rhs) const
{
    return (sec != rhs.sec) || (nsec != rhs.nsec);
}

bool Timestamp::operator<(const Timestamp& rhs) const
{
    if (sec == rhs.sec) {
        return nsec < rhs.nsec;
    } else {
        return sec < rhs.sec;
    }
}

bool Timestamp::operator>(const Timestamp& rhs) const
{
    if (sec == rhs.sec) {
        return nsec > rhs.nsec;
    } else {
        return sec > rhs.sec;
    }
}

bool Timestamp::operator<=(const Timestamp& rhs) const
{
    if (sec == rhs.sec) {
        return nsec <= rhs.nsec;
    } else {
        return sec < rhs.sec;
    }
}

bool Timestamp::operator>=(const Timestamp& rhs) const
{
    if (sec == rhs.sec) {
        return nsec >= rhs.nsec;
    } else {
        return sec >= rhs.sec;
    }
}

double Timestamp::to_double() const
{
    return sec + nsec / 1e9;
}


Timestamp get_timestamp(int source)
{
    timespec tspec;
    // TODO: deal with year 2038
    timespec_get(&tspec, source);
    return Timestamp(tspec.tv_sec, static_cast<int32_t>(tspec.tv_nsec));
}

}
