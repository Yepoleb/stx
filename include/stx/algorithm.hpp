#pragma once
#include <algorithm>
#include <functional>



namespace stx {

template <typename T>
constexpr const T& constrain_max(const T& a, const T& b)
{
    return std::min(a, b);
}

template <typename T>
constexpr const T& constrain_min(const T& a, const T& b)
{
    return std::max(a, b);
}

template <typename T>
constexpr const T& constrain(const T& a, const T& b, const T& val)
{
    if (a < b) {
        return constrain_min(constrain_max(b, val), a);
    } else {
        return constrain_min(constrain_max(a, val), b);
    }
}

template<typename IterableT, typename CompareT>
bool compare_iter(
    const IterableT& iterable1, const IterableT& iterable2, CompareT compare)
{
    auto iter1 = iterable1.cbegin();
    auto iter2 = iterable2.cbegin();
    auto end1 = iterable1.cend();
    auto end2 = iterable2.cend();

    while (true) {
        auto cur1 = iter1++;
        auto cur2 = iter2++;
        assert(cur2 != end2);

        if (iter1 == end1) { // Last element
            return compare(*cur1, *cur2);
        }
        if (*cur1 != *cur2) {
            return compare(*cur1, *cur2);
        }
    }
}

template<typename IterableT>
bool equal_iter(const IterableT& iterable1, const IterableT& iterable2)
{
    auto iter1 = iterable1.cbegin();
    auto iter2 = iterable2.cbegin();
    auto end1 = iterable1.cend();
    auto end2 = iterable2.cend();

    for (;iter1 != end1; iter1++, iter2++) {
        assert(iter2 != end2);

        if (*iter1 != *iter2) {
            return false;
        }
    }
    return true;
}

template<typename IterableT>
bool not_equal_iter(const IterableT& iterable1, const IterableT& iterable2)
{
    return !equal_iter(iterable1, iterable2);
}

template<typename IterableT>
bool greater_iter(const IterableT& iterable1, const IterableT& iterable2)
{
    using value_type = decltype(*iterable1.cbegin());
    return compare_iter(
        iterable1, iterable2, std::greater<value_type>());
}

template<typename IterableT>
bool greater_equal_iter(const IterableT& iterable1, const IterableT& iterable2)
{
    using value_type = decltype(*iterable1.cbegin());
    return compare_iter(
        iterable1, iterable2, std::greater_equal<value_type>());
}

template<typename IterableT>
bool less_iter(const IterableT& iterable1, const IterableT& iterable2)
{
    using value_type = decltype(*iterable1.cbegin());
    return compare_iter(
        iterable1, iterable2, std::less<value_type>());
}

template<typename IterableT>
bool less_equal_iter(const IterableT& iterable1, const IterableT& iterable2)
{
    using value_type = decltype(*iterable1.cbegin());
    return compare_iter(
        iterable1, iterable2, std::less_equal<value_type>());
}

}
