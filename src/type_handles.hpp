#include "bind_core.hpp"
#include "type_str/scalars.hpp"
#include "scalar_wrapper.hpp"

template <typename T, template <typename...> typename Template>
struct is_specialization_of : std::false_type {};

template <template <typename...> typename Template, typename... Args>
struct is_specialization_of<Template<Args...>, Template> : std::true_type {};

template <typename T, template <typename...> typename Template>
inline constexpr bool is_specialization_of_v = is_specialization_of<T, Template>::value;

namespace types {
  template <typename T>
  nanobind::handle handle_for() {
    if constexpr (std::is_same_v<std::decay_t<T>, std::string> ||
                  std::is_integral_v<std::decay_t<T>> ||
                  std::is_floating_point_v<std::decay_t<T>> ||
                  is_specialization_of_v<std::decay_t<T>, std::pair>)
      return nanobind::type<scalar_wrapper<T>>();
    else
      return nanobind::type<T>();
  }
}
