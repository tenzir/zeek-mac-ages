#ifndef BRO_PLUGIN_TENZIR_TRIE
#define BRO_PLUGIN_TENZIR_TRIE

#include <plugin/Plugin.h>

#include <broker/detail/radix_tree.hh>

#include <array>
#include <chrono>
#include <cstdint>
#include <cstddef>
#include <string>

namespace plugin {
namespace tenzir {
namespace mac_ages {

/// The age of a MAC address.
using age_type = std::chrono::system_clock::time_point;

/// A trie data structure for MAC addresses. Internally, this class uses an
/// ART trie to store prefixes of MAC addresses.
class mac_trie {
public:
  /// Loads a CSV file where each line has the following format:
  ///
  ///    000000000000/24,2000-09-08,deepmac.org
  ///
  /// @param csv_file The name of the CSV file to load.
  /// @returns The number entries loaded or -1 if the file cannot be read.
  long load(const std::string& csv_file); 

  /// Performs a prefix-lookup of a MAC address.
  /// @param str The beginning of the MAC address string.
  /// @param size The length of *str*.
  /// @returns The age of *mac* or the UNIX epoch of no prefix was found.
  age_type lookup(const char* str, size_t size) const;

private:
  bool add(const std::string& mac, uint8_t length, age_type age);

  // Using this radix tree implementation is not ideal, because it does not
  // support specification of the number of bits of the key when performing a
  // prefix lookup. Thus, we currently perform a space-inefficient conversion
  // into a binary string that stores each bit as single character. Once we
  // have a better radix tree implementation (a PATRICIA trie would be great
  // here), we can get a factor 8 in space reduction.
  broker::detail::radix_tree<age_type> radix_tree_;
};

extern mac_trie data;

} // namespace mac_ages
} // namespace tenzir
} // namespace plugin

#endif
