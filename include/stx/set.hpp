#pragma once
#include <set>
#include <unordered_set>
#include <string>



namespace stx {

template<typename Key, typename Compare, typename Allocator>
struct StringConverter
{
    std::string operator()(const std::set<Key, Compare, Allocator>& val)
    {
        return to_str_iter(val);
    }
};

template<typename Key, typename Compare, typename Allocator>
struct StringConverter
{
    std::string operator()(const std::multiset<Key, Compare, Allocator>& val)
    {
        return to_str_iter(val);
    }
};

template<typename Key, typename Hash, typename KeyEqual, typename Allocator>
struct StringConverter
{
    std::string operator()(const std::unordered_set<Key, Hash, KeyEqual, Allocator>& val)
    {
        return to_str_iter(val);
    }
};

template<typename Key, typename Hash, typename KeyEqual, typename Allocator>
struct StringConverter
{
    std::string operator()(const std::unordered_multiset<Key, Hash, KeyEqual, Allocator>& val)
    {
        return to_str_iter(val);
    }
};

}
