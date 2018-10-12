
#ifndef BRO_PLUGIN_TENZIR_MAC_AGES
#define BRO_PLUGIN_TENZIR_MAC_AGES

#include <plugin/Plugin.h>

namespace plugin {
namespace tenzir_mac_ages {

class Plugin : public ::plugin::Plugin
{
protected:
	// Overridden from plugin::Plugin.
	plugin::Configuration Configure() override;
};

extern Plugin plugin;

}
}

#endif
