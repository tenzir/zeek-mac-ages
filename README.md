Zeek & MAC Address Ages
=======================

This [Zeek](https://zeek.org) plugin adds functionality to query the age of a
MAC address. The data comes from HD Moore's [MAC Adress Age
Tracking](https://github.com/hdm/mac-ages) repository, which is a curated
database of MAC addresses bootstrapped from the
[DeepMAC](http://www.deepmac.org) and [Wireshark](http://www.wireshark.org)
archives. A bot pulls from an IEEE website daily to keep the data up to date.

Usage
-----

First, install the package with the [Zeek package
manager](https://github.com/zeek/package-manager):

```sh
zkg install tenzir/zeek-mac-ages
```

Then make sure that you have a recent version of the MAC database installed
somewhere. Set the environment variable `ZEEK_TENZIR_MAC_AGES_CSV` to the CSV
file and you're set to load the plugin:

```zeek
@load tenzir/mac-ages
```

By default, the script enhances the stock DHCP log with a field `mac_age`
containing the approximate "birthday" of a MAC address in YYYY-MM-DD format.
Here's an example log file generated with a [sample trace from the Wireshark
wiki](https://wiki.wireshark.org/SampleCaptures):

```
#separator \x09
#set_separator	,
#empty_field	(empty)
#unset_field	-
#path	dhcp
#open	2018-12-28-15-47-11
#fields	ts	uids	client_addr	server_addr	mac	host_name	client_fqdn	domain	requested_addr	assigned_addr	lease_time	client_message	server_message	msg_types	duration	mac_age
#types	time	set[string]	addr	addr	string	string	string	string	addr	addr	interval	string	string	vector[string]	interval	string
1102274184.387484	CMnxGv1YFAUvoaADr2,CzdoL23dzCo4Zuq0d8	192.168.0.10	192.168.0.1	00:0b:82:01:fc:42	-	-	-	192.168.0.10	192.168.0.10	3600.000000	-	-	REQUEST,ACK	0.000314	2002-10-14
1102274184.317453	CMnxGv1YFAUvoaADr2,CzdoL23dzCo4Zuq0d8	192.168.0.10	192.168.0.1	00:0b:82:01:fc:42	-	-	-	0.0.0.0	192.168.0.10	3600.000000	-	-	DISCOVER,OFFER	0.000295	2002-10-14
#close	2018-12-28-15-47-11
```

For more fine-grained control, have a lok at the [new builtin
functions](src/mac_ages.bif) (BiFs) for replacing the MAC age database
addresses and performing lookups a MAC addresses.

Development
-----------

If you want to compile the plugin from scratch, use the accompanying
[`configure`](configure) helper script:

```sh
export ZEEK=/path/to/zeek-dist
./configure --zeek-dist="$ZEEK"
cd build
make
```

After the compilation succeeded, notify Zeek about the plugin:

```sh
export ZEEK_PLUGIN_PATH=$(pwd)
export ZEEKPATH="$($ZEEK/build/zeek-path-dev):$ZEEK_PLUGIN_PATH/.."
alias zeek=$ZEEK/build/src/zeek
zeek -N | grep tenzir
```

This should print:


```
tenzir::mac_ages - MAC address age estimation (dynamic, version 0.1.0)
```

You can now play with code. For example, to generate the above log file:

```
wget https://github.com/hdm/mac-ages/raw/master/data/mac-ages.csv
export ZEEK_TENZIR_MAC_AGES_CSV=mac-ages.csv
zeek -C -r $ZEEK/testing/btest/Traces/dhcp/dhcp.trace tenzir/mac-ages
```

This should generate a `dhcp.log` `2012-07-11` in the column `mac_age` for the
MAC address `90:b1:1c:99:49:29`.

LICENSE
-------

This plugin comes with a BSD license.
