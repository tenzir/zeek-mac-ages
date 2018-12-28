##! Add a field with the approximate age of a MAC address to the DHCP log.

@load base/protocols/dhcp

@load ./utils.bro

module DHCP;

export {
	redef record DHCP::Info += {
		## The approximate age of the MAC address in the `mac` field.
		mac_age: string &log &optional;
	};
}

event DHCP::aggregate_msgs(ts: time, id: conn_id, uid: string, is_orig: bool,
                           msg: DHCP::Msg, options: DHCP::Options)
	{
	if ( ! log_info?$mac )
	  return;
  local mac_age = Tenzir::ymd_mac_age(log_info$mac);
  if ( mac_age != "1970-01-01" )
    log_info$mac_age = mac_age;
	}
