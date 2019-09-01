# @TEST-EXEC: zeek %INPUT > output
# @TEST-EXEC: btest-diff output

event zeek_init()
	{
	local filename = getenv("MAC_AGES_CSV");
	print load_mac_ages(filename);
	}
