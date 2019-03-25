#!/bin/bash

if [ -z "$2" ]; then
	echo "Use: $0 <iface> <file>"
	exit
fi 

DEV=${1}
FIRM="$2"
FILENAME=$(basename $2)
 
TFTPD="/tmp/tftp"
mkdir -p $TFTPD
cp -f "$2" $TFTPD/$FILENAME

echo "Using dev $DEV"
killall dnsmasq
echo 1 > /proc/sys/net/ipv4/ip_forward
iptables -A POSTROUTING -t nat -j MASQUERADE

ip addr add 192.168.1.10/24 dev $DEV
ip link set dev $DEV up

dnsmasq -F 192.168.1.100,192.168.1.200 -i $DEV --enable-tftp --tftp-root $TFTPD \
 -d -p0 -K --log-dhcp --bootp-dynamic




