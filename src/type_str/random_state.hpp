#ifndef SRC_TYPE_STR_RANDOM_STATE_HPP_
#define SRC_TYPE_STR_RANDOM_STATE_HPP_

#include <random>

#include "common.hpp"

// random_state
template <>
struct type_str<std::mt19937_64> {
  std::string operator()() { return "mersenne_twister"; }
};

#endif  // SRC_TYPE_STR_RANDOM_STATE_HPP_
