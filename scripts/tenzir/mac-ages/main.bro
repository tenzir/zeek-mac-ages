module Tenzir;

export {
	## The filename containing the MAC address ages.
	const mac_ages_file = "mac-ages.csv" &redef;

	## Load a database of MAC addresses for later lookup via
	## :bro:see:`lookup_mac_age`.
	##
	## filename: The CSV file containing the MAC address ages.
	##
	## Returns: the number of prefix loaded.
	global load_mac_ages: function(filename: string): count;

	## Retrives the approximate age of a MAC address.
	##
	## mac: The MAC address whose age to lookup.
	##
	## Returns: The approximate age of the MAC address.
	global lookup_mac_age: function(mac: string): interval;
};
