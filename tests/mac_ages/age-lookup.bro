# @TEST-EXEC: bro %INPUT > output
# @TEST-EXEC: btest-diff output

function ymd_age(mac: string): string
	{
	return strftime("%Y-%m-%d", lookup_mac_age(mac));
	}

event bro_init()
	{
	# Load the full file.
	local filename = getenv("MAC_AGES_CSV");
	print load_mac_ages(filename);
	# Test an example entry in various MAC address formats:
	# fe64ba000000/24,2015-08-29,deepmac.org
	print ymd_age("fe64ba000000");
	print ymd_age("fe:64:ba:00:00:00");
	print ymd_age("FE:64:BA:00:00:00");
	# Fill the last 3 bytes with anything and still expect a match.
	print ymd_age("fe64baffffff");
	# But if we scratch the 3rd byte, we no longer have a match.
	print lookup_mac_age("fe6400000000");
	}
