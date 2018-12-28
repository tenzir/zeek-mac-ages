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
bro-pkg install tenzir/mac-ages
```

Then make sure that you have a recent version of the MAC database installed
somewhere. Set the environment variable `BRO_TENZIR_MAC_AGES_CSV` to the CSV
file and you're set to load the plugin:

```bro
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
export BRO=/path/to/bro-dist
./configure --bro-dist="$BRO"
cd build
make
```

After the compilation succeeded, notify Bro about the plugin:

```sh
export BRO_PLUGIN_PATH=$(pwd)
export BROPATH="$($BRO/build/bro-path-dev):$BRO_PLUGIN_PATH/.."
alias bro=$BRO/build/src/bro
bro -N | grep tenzir 
```

This should print:


```
tenzir::mac_ages - MAC address age estimation (dynamic, version 0.1.0)
```

You can now play with code. For example, generate the above log file:

```
bro -C -r dhcp.pcap tenzir/mac-ages
```

LICENSE
-------

This plugin comes with BSD license.
