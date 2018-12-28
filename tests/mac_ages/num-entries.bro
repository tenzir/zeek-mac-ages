# @TEST-EXEC: bro %INPUT > output
# @TEST-EXEC: btest-diff output

event bro_init()
	{
	local filename = getenv("MAC_AGES_CSV");
	print load_mac_ages(filename);
	}
