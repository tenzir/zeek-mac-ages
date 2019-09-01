# @TEST-EXEC: zeek %INPUT > output
# @TEST-EXEC: btest-diff output

function ymd_age(x: string): string
	{
	return strftime("%Y-%m-%d", lookup_mac_age(x));
	}

event zeek_init()
	{
	# Shows the number of loaded entries.
	print load_mac_ages("../../data.csv");
	print "--------------------------";
	# No match; returns UNIX epoch.
	print ymd_age("aa:aa:aa:aa:aa:aa");
	print ymd_age("00:00:00:00:00:00");
	print ymd_age("00:00:00:10:00:00");
	print ymd_age("00:00:00:20:00:00");
	print ymd_age("00:00:00:30:00:00");
	print ymd_age("00:00:00:40:00:00");
	print ymd_age("00:00:00:50:00:00");
	print ymd_age("00:00:00:60:00:00");
	print ymd_age("00:00:00:70:00:00");
	print "--------------------------";
	# Matches the first entry.
	print ymd_age("00:00:00:80:00:00");
	print ymd_age("00:00:00:90:00:00");
	print ymd_age("00:00:00:a0:00:00");
	print ymd_age("00:00:00:b0:00:00");
	print "--------------------------";
	# Matches the second entry (longer prefix).
	print ymd_age("00:00:00:c0:00:00");
	print ymd_age("00:00:00:d0:00:00");
	print ymd_age("00:00:00:e0:00:00");
	print ymd_age("00:00:00:f0:00:00");
	print "--------------------------";
	}
