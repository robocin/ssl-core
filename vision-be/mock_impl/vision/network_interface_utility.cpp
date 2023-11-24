#include "vision/network_interface_utility.h"

#include <arpa/inet.h>
#include <array>
#include <ifaddrs.h>
#include <net/if.h>
#include <netinet/in.h>
#include <string_view>
#include <sys/socket.h>
#include <sys/types.h>
#include <system_error>
#include <unistd.h>

namespace robocin {

bool network_interface_utility::contains(std::string_view interface_name) noexcept(false) {
  ::ifaddrs* addresses_begin = nullptr;

  if (::getifaddrs(&addresses_begin) == -1) {
    throw std::system_error(errno,
                            std::system_category(),
                            "getifaddrs: error getting network interfaces.");
  }

  for (::ifaddrs* ptr = addresses_begin; ptr != nullptr; ptr = ptr->ifa_next) {
    if ((ptr->ifa_name != nullptr) && std::string_view{ptr->ifa_name} == interface_name) {
      return ::freeifaddrs(addresses_begin), true;
    }
  }

  return ::freeifaddrs(addresses_begin), false;
}
std::string
network_interface_utility::address_from(std::string_view interface_name) noexcept(false) {
  ::ifaddrs* addresses_begin = nullptr;

  if (::getifaddrs(&addresses_begin) == -1) {
    throw std::system_error(errno,
                            std::system_category(),
                            "getifaddrs: error getting network interfaces.");
  }

  for (::ifaddrs* ptr = addresses_begin; ptr != nullptr; ptr = ptr->ifa_next) {
    if ((ptr->ifa_name != nullptr) && std::string_view{ptr->ifa_name} == interface_name) {
      if (ptr->ifa_addr == nullptr) {
        throw std::system_error(errno,
                                std::system_category(),
                                "getifaddrs: error getting network interfaces.");
      }

      if (ptr->ifa_addr->sa_family == AF_INET) {
        auto* addr = reinterpret_cast<sockaddr_in*>(ptr->ifa_addr); // NOLINT(*reinterpret-cast*)

        std::array<char, INET_ADDRSTRLEN> buffer{};
        ::inet_ntop(AF_INET, &(addr->sin_addr), buffer.data(), INET_ADDRSTRLEN);

        return ::freeifaddrs(addresses_begin), std::string{buffer.data()};
      }
    }
  }

  return ::freeifaddrs(addresses_begin), ""; // NOLINT(*decay*)
}
std::vector<std::string> network_interface_utility::all_interface_names() noexcept(false) {
  std::vector<std::string> result;
  ::ifaddrs* addresses_begin = nullptr;

  if (::getifaddrs(&addresses_begin) == -1) {
    throw std::system_error(errno,
                            std::system_category(),
                            "getifaddrs: error getting network interfaces.");
  }

  for (::ifaddrs* ptr = addresses_begin; ptr != nullptr; ptr = ptr->ifa_next) {
    if (ptr->ifa_name != nullptr) {
      result.emplace_back(ptr->ifa_name);
    }
  }

  return ::freeifaddrs(addresses_begin), result;
}
std::vector<std::pair<std::string, std::string>>
network_interface_utility::all_interface_entries() noexcept(false) {
  std::vector<std::pair<std::string, std::string>> result;
  ::ifaddrs* addresses_begin = nullptr;

  if (::getifaddrs(&addresses_begin) == -1) {
    throw std::system_error(errno,
                            std::system_category(),
                            "getifaddrs: error getting network interfaces.");
  }

  for (::ifaddrs* ptr = addresses_begin; ptr != nullptr; ptr = ptr->ifa_next) {
    if (ptr->ifa_name != nullptr) {
      if (ptr->ifa_addr == nullptr) {
        throw std::system_error(errno,
                                std::system_category(),
                                "getifaddrs: error getting network interfaces.");
      }

      if (ptr->ifa_addr->sa_family == AF_INET) {
        auto* addr = reinterpret_cast<sockaddr_in*>(ptr->ifa_addr); // NOLINT(*reinterpret-cast*)

        std::array<char, INET_ADDRSTRLEN> buffer{};
        ::inet_ntop(AF_INET, &(addr->sin_addr), buffer.data(), INET_ADDRSTRLEN);

        result.emplace_back(ptr->ifa_name, std::string{buffer.data()});
      }
    }
  }

  return ::freeifaddrs(addresses_begin), result;
}

} // namespace robocin
