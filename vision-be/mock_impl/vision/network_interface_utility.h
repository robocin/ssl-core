#include <string>
#include <vector>

namespace robocin {

// NOLINTBEGIN(*naming*)
class network_interface_utility {
 public:
  network_interface_utility() = delete;

  network_interface_utility(const network_interface_utility&) = delete;
  network_interface_utility& operator=(const network_interface_utility&) = delete;

  network_interface_utility(network_interface_utility&&) = delete;
  network_interface_utility& operator=(network_interface_utility&&) = delete;

  ~network_interface_utility() = delete;

  // O(n)
  static bool contains(std::string_view interface_name) noexcept(false);

  // O(n)
  static std::string address_from(std::string_view interface_name) noexcept(false);

  // O(n)
  static std::vector<std::string> all_interface_names() noexcept(false);

  // O(n)
  static std::vector<std::pair<std::string, std::string>> all_interface_entries() noexcept(false);
};
// NOLINTEND(*naming*)

} // namespace robocin
