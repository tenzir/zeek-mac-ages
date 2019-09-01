@load base/frameworks/reporter

module Tenzir;

export {

## Performs a lookup of the approximate age of a MAC address.
## mac: The MAC address whose age to lookup.
## Returns: A YYYY-MM-DD string representing the "birthday" of *mac*.
global ymd_mac_age: function(mac: string): string;

## Attempts to load a CSV file containing the MAC age database from an
## environment variable
## env: The environment variable containing the path to the CSV file.
## Returns: The number of entries in the file pointed to by *env* or -1 on
##          failure.
global load_mac_ages_from_env: function(env: string): int;

}

function ymd_mac_age(mac: string): string
	{
	return strftime("%Y-%m-%d", lookup_mac_age(mac));
	}

function load_mac_ages_from_env(env: string): int
  {
  local mac_ages_csv = getenv(env);
  local num_entries = load_mac_ages(mac_ages_csv);
  if ( num_entries == -1 )
    Reporter::error(fmt("failed to load MAC ages from %s", mac_ages_csv));
  return num_entries;
  }
