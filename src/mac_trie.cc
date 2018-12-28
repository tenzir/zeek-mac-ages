#include "mac_trie.h"

#include <caf/variant.hpp>

#include <fstream>

#include <cctype>
#include <ctime>
#include <cstdio>
#include <string>

namespace plugin {
namespace tenzir {
namespace mac_ages {

namespace {

int to_int(char x) {
  if (x >= '0' && x <= '9')
    return x - '0';
  if (x >= 'a' && x <= 'j')
    return x - 'a' + 10;
  return 0;
}

uint8_t to_byte(char hi, char lo) {
  return to_int(hi) * 16 + to_int(lo);
}

std::string to_binary_string(const std::string& mac) {
  std::string result;
  result.reserve(48);
  assert(mac.size() % 2 == 0);
  for (size_t i = 0; i < mac.size(); i += 2) {
    auto byte = to_byte(mac[i], mac[i + 1]);
    size_t n = 8;
    while (n-- > 0) {
      auto mask = 1 << n;
      result += (byte & mask) == mask ? '1' : '0';
    }
  }
  return result;
}

bool starts_with(const std::string& str, const std::string& prefix) {
  return str.compare(0, prefix.size(), prefix) == 0;
}

// Creates a normalized version of a MAC address.
std::string normalize(const char* data, size_t size) {
  std::string result;
  for (size_t i = 0; i < size; ++i)
    if (data[i] != ':')
      result += std::tolower(data[i]);
  return result.size() <= 12 ? result : "";
}

} // namespace anonymous

long mac_trie::load(const std::string& csv_file) {
  std::ifstream file{csv_file};
  if (!file)
    return -1;
  auto result = 0;
  std::string line;
  char mac[12];
  uint8_t length;
  std::tm tm;
  char source[64];
  auto format = "%12s/%2u,%4d-%2d-%2d,%64s";
  while (std::getline(file, line)) {
    std::memset(mac, 0, sizeof(mac));
    std::memset(&tm, 0, sizeof(tm));
    std::memset(source, 0, sizeof(source));
    auto n = std::sscanf(line.c_str(), format, mac, &length,
                         &tm.tm_year, &tm.tm_mon, &tm.tm_mday, source);
    if (n == 0 || length == 0 || length > 48)
      return result;
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    auto age = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    if (!add(mac, length, age))
      return result;
    ++result;
  }
  return result;
}

age_type mac_trie::lookup(const char* data, size_t size) const {
  auto bits = to_binary_string(normalize(data, size));
  auto xs = radix_tree_.prefix_of(bits);
  auto result = age_type::min();
  const std::string* longest_prefix = nullptr;
  for (size_t i = 0; i < xs.size(); ++i) {
    auto prefix = &xs[i]->first;
    // This check should ideally not be needed. But the function prefix_of
    // returns shared prefixes, so we need to perform a candidate check here.
    if (!starts_with(bits, *prefix))
      continue;
    if (longest_prefix == nullptr || longest_prefix->size() < prefix->size()) {
      longest_prefix = prefix;
      result = xs[i]->second;
    }
  }
  return result;
}

bool mac_trie::add(const std::string& mac, uint8_t length, age_type age) {
  assert(mac.size() == 12);
  auto bits = to_binary_string(normalize(mac.data(), mac.size()));
  assert(length <= bits.size());
  bits.resize(length);
  radix_tree_.insert(std::make_pair(bits, age));
  return true;
}

mac_trie data;

} // namespace mac_ages
} // namespace tenzir
} // namespace plugin
