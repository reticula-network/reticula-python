#ifndef SRC_TYPE_STR_COMMON_HPP_
#define SRC_TYPE_STR_COMMON_HPP_

#include <string>
#include <algorithm>

template<typename T> struct type_str {
    std::string operator()();
};

template<typename T>
std::string python_type_str() {
    auto s = type_str<T>{}();
    std::ranges::replace(s, '[', '_');
    std::ranges::replace(s, ',', '_');
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    s.erase(std::remove(s.begin(), s.end(), ']'), s.end());
    return s;
}

#endif  // SRC_TYPE_STR_COMMON_HPP_
