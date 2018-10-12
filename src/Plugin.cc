#include "Plugin.h"

namespace plugin {
namespace tenzir {
namespace mac_ages {

Plugin plugin;

Configuration Plugin::Configure()
	{
	Configuration config;
	config.name = "tenzir::mac_ages";
	config.description = "<Insert description>";
	config.version.major = 0;
	config.version.minor = 1;
	return config;
	}

} // namespace mac_ages
} // namespace tenzir
} // namespace plugin
