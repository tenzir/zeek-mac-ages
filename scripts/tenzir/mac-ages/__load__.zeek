@load ./dhcp.zeek
@load ./utils.zeek

event zeek_init() {
  Tenzir::load_mac_ages_from_env("ZEEK_TENZIR_MAC_AGES_CSV");
}
