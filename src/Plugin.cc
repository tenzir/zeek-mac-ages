
#include "Plugin.h"

namespace plugin { namespace tenzir_mac_ages { Plugin plugin; } }

using namespace plugin::tenzir_mac_ages;

plugin::Configuration Plugin::Configure()
	{
	plugin::Configuration config;
	config.name = "tenzir::mac_ages";
	config.description = "<Insert description>";
	config.version.major = 0;
	config.version.minor = 1;
	return config;
	}
