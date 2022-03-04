#ifndef SRC_TYPE_STR_SCALARS_HPP_
#define SRC_TYPE_STR_SCALARS_HPP_

#include <string>
#include <utility>
#include <cstdint>

#include <fmt/format.h>

#include "common.hpp"

// signed integer
template <>
struct type_str<int8_t>  { std::string operator()() { return "int8"; } };

template <>
struct type_str<int16_t> { std::string operator()() { return "int16"; } };

template <>
struct type_str<int32_t> { std::string operator()() { return "int32"; } };

template <>
struct type_str<int64_t> { std::string operator()() { return "int64"; } };

template <>
struct type_str<uint8_t>  { std::string operator()() { return "uint8"; } };

template <>
struct type_str<uint16_t> { std::string operator()() { return "uint16"; } };

template <>
struct type_str<uint32_t> { std::string operator()() { return "uint32"; } };

template <>
struct type_str<uint64_t> { std::string operator()() { return "uint64"; } };


// floating point
template <>
struct type_str<float> { std::string operator()()       { return "float"; } };

template <>
struct type_str<double> { std::string operator()()      { return "double"; } };

template <>
struct type_str<long double> { std::string operator()() { return "ldouble"; } };

// non-integer types
template <>
struct type_str<std::string> { std::string operator()() { return "string"; } };

template <typename T1, typename T2>
struct type_str<std::pair<T1, T2>> {
  std::string operator()() {
    return fmt::format("pair[{}, {}]", type_str<T1>{}(), type_str<T2>{}());
  }
};

#endif  // SRC_TYPE_STR_SCALARS_HPP_
