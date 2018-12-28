@load ./dhcp.bro
@load ./utils.bro

event bro_init() {
  Tenzir::load_mac_ages_from_env("BRO_TENZIR_MAC_AGES_CSV");
}
