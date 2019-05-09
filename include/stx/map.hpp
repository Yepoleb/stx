#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include <stringstream>



namespace stx {

template<typename T>
class MapKeyIterator : public T
{
public:
    MapKeyIterator() : T() {}
    MapKeyIterator(T iter) : T(iter) {}

    auto* operator->()
    {
        return &(T::operator->()->first);
    }

    auto& operator*()
    {
        return T::operator *().first;
    }
};

template<typename T>
class ConstMapKeyIterator : public T
{
public:
    ConstMapKeyIterator() : T() {}
    ConstMapKeyIterator(T iter) : T(iter) {}

    const auto* operator->()
    {
        return &(T::operator->()->first);
    }

    const auto& operator*()
    {
        return T::operator*().first;
    }
};

template<typename T>
class MapKeyAdaptor
{
public:
    MapKeyAdaptor(T& m_) : m(m_) {}

    auto begin() noexcept
    {
        return MapKeyIterator<typename T::iterator>(m.begin());
    }

    auto begin() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_iterator>(m.begin());
    }

    auto end() noexcept
    {
        return MapKeyIterator<typename T::iterator>(m.end());
    }

    auto end() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_iterator>(m.end());
    }

    auto rbegin() noexcept
    {
        return MapKeyIterator<typename T::reverse_iterator>(m.rbegin());
    }

    auto rbegin() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_reverse_iterator>(m.rbegin());
    }

    auto rend() noexcept
    {
        return MapKeyIterator<typename T::reverse_iterator>(m.rbegin());
    }

    auto rend() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_reverse_iterator>(m.rend());
    }

    auto cbegin() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_iterator>(m.cbegin());
    }

    auto cend() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_iterator>(m.cend());
    }

    auto crbegin() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_reverse_iterator>(m.crbegin());
    }

    auto crend() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_reverse_iterator>(m.crend());
    }

protected:
    T& m;
};

template<typename T>
class ConstMapKeyAdaptor
{
public:
    ConstMapKeyAdaptor(const T& m_) : m(m_) {}

    auto begin() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_iterator>(m.begin());
    }

    auto end() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_iterator>(m.end());
    }

    auto rbegin() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_reverse_iterator>(m.rbegin());
    }

    auto rend() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_reverse_iterator>(m.rend());
    }

    auto cbegin() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_iterator>(m.cbegin());
    }

    auto cend() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_iterator>(m.cend());
    }

    auto crbegin() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_reverse_iterator>(m.crbegin());
    }

    auto crend() const noexcept
    {
        return ConstMapKeyIterator<typename T::const_reverse_iterator>(m.crend());
    }

protected:
    const T& m;
};

template<typename T>
MapKeyAdaptor<T> keys(T& m)
{
    return MapKeyAdaptor<T>(m);
}

template<typename T>
ConstMapKeyAdaptor<T> keys(const T& m)
{
    return ConstMapKeyAdaptor<T>(m);
}

template<typename T>
class MapValueIterator : public T
{
public:
    MapValueIterator() : T() {}
    MapValueIterator(T iter) : T(iter) {}

    auto* operator->()
    {
        return &(T::operator->()->second);
    }

    auto& operator*()
    {
        return T::operator*().second;
    }
};

template<typename T>
class ConstMapValueIterator : public T
{
public:
    ConstMapValueIterator() : T() {}
    ConstMapValueIterator(T iter) : T(iter) {}

    const auto* operator->()
    {
        return &(T::operator->()->second);
    }

    const auto& operator*()
    {
        return T::operator*().second;
    }
};

template<typename T>
class MapValueAdaptor
{
public:
    MapValueAdaptor(T& m_) : m(m_) {}

    auto begin() noexcept
    {
        return MapValueIterator<typename T::iterator>(m.begin());
    }

    auto begin() const noexcept
    {
        return ConstMapValueIterator<typename T::const_iterator>(m.begin());
    }

    auto end() noexcept
    {
        return MapValueIterator<typename T::iterator>(m.end());
    }

    auto end() const noexcept
    {
        return ConstMapValueIterator<typename T::const_iterator>(m.end());
    }

    auto rbegin() noexcept
    {
        return MapValueIterator<typename T::reverse_iterator>(m.rbegin());
    }

    auto rbegin() const noexcept
    {
        return ConstMapValueIterator<typename T::const_reverse_iterator>(m.rbegin());
    }

    auto rend() noexcept
    {
        return MapValueIterator<typename T::reverse_iterator>(m.rbegin());
    }

    auto rend() const noexcept
    {
        return ConstMapValueIterator<typename T::const_reverse_iterator>(m.rend());
    }

    auto cbegin() const noexcept
    {
        return ConstMapValueIterator<typename T::const_iterator>(m.cbegin());
    }

    auto cend() const noexcept
    {
        return ConstMapValueIterator<typename T::const_iterator>(m.cend());
    }

    auto crbegin() const noexcept
    {
        return ConstMapValueIterator<typename T::const_reverse_iterator>(m.crbegin());
    }

    auto crend() const noexcept
    {
        return ConstMapValueIterator<typename T::const_reverse_iterator>(m.crend());
    }

protected:
    T& m;
};

template<typename T>
class ConstMapValueAdaptor
{
public:
    ConstMapValueAdaptor(const T& m_) : m(m_) {}

    auto begin() const noexcept
    {
        return ConstMapValueIterator<typename T::const_iterator>(m.begin());
    }

    auto end() const noexcept
    {
        return ConstMapValueIterator<typename T::const_iterator>(m.end());
    }

    auto rbegin() const noexcept
    {
        return ConstMapValueIterator<typename T::const_reverse_iterator>(m.rbegin());
    }

    auto rend() const noexcept
    {
        return ConstMapValueIterator<typename T::const_reverse_iterator>(m.rend());
    }

    auto cbegin() const noexcept
    {
        return ConstMapValueIterator<typename T::const_iterator>(m.cbegin());
    }

    auto cend() const noexcept
    {
        return ConstMapValueIterator<typename T::const_iterator>(m.cend());
    }

    auto crbegin() const noexcept
    {
        return ConstMapValueIterator<typename T::const_reverse_iterator>(m.crbegin());
    }

    auto crend() const noexcept
    {
        return ConstMapValueIterator<typename T::const_reverse_iterator>(m.crend());
    }

protected:
    const T& m;
};

template<typename T>
MapValueAdaptor<T> values(T& m)
{
    return MapValueAdaptor<T>(m);
}

template<typename T>
ConstMapValueIterator<T> values(const T& m)
{
    return ConstMapValueIterator<T>(m);
}


template<typename T>
std::string to_str_map(const T& val)
{
    std::stringstream ss;
    ss << '{';
    auto begin = val.cbegin();
    auto end = val.cend();
    for (auto it = begin; it != end; ++it) {
        if (it != begin) {
            ss << ", ";
        }
        const auto& map_pair = *it;
        ss << to_repr(map_pair.first) << ": "
            << to_repr(map_pair.second);
    }
    ss << '}';

    return ss.str();
}

template<typename Key, typename T, typename Compare, typename Allocator>
struct StringConverter
{
    std::string operator()(const std::map<Key, T, Compare, Allocator>& val)
    {
        return to_str_map(val);
    }
};

template<typename Key, typename T, typename Compare, typename Allocator>
struct StringConverter
{
    std::string operator()(const std::multimap<Key, T, Compare, Allocator>& val)
    {
        return to_str_map(val);
    }
};

template<typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
struct StringConverter
{
    std::string operator()(const std::unordered_map<Key, T, Hash, KeyEqual, Allocator>& val)
    {
        return to_str_map(val);
    }
};

template<typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
struct StringConverter
{
    std::string operator()(const std::unordered_multimap<Key, T, Hash, KeyEqual, Allocator>& val)
    {
        return to_str_map(val);
    }
};

}
