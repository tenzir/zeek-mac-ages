#pragma once

#include <plugin/Plugin.h>

namespace plugin {
namespace tenzir {
namespace mac_ages {

class Plugin : public ::plugin::Plugin
{
protected:
	// Overridden from plugin::Plugin.
	plugin::Configuration Configure() override;
};

extern Plugin plugin;

} // namespace mac_ages
} // namespace tenzir
} // namespace plugin
