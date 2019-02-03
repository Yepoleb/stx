#pragma once
#include <pair>
#include <functional>
#include <stddef.h>



namespace std {
    template <typename T1, typename T2>
    struct hash<std::pair<T1, T2>>
    {
        typedef std::pair<T1, T2> argument_type;
        typedef size_t result_type;
        result_type operator()(const argument_type& value) const noexcept
        {
            return
                std::hash<T1>()(value.first) |
                (std::hash<T2>()(value.second) << 1);
        }
    };
}
