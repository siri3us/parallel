#!/bin/bash

# Step 1. Creating correct network config file
ARGS=""
MASK="255.255.255.0"
# There is must be a host number at the end
IP_ADDRESS_BASE="192.168.56." 
# Default host number
HOST_NUMBER="0" 

NETWORK_CONFIG_FILE="/etc/network/interfaces"

while (( $# > 0 )); do
  arg=$1
  shift
  case $arg in
    --host-number|-n)
      HOST_NUMBER=$1
      shift;;
    --config-file|-f)
      NETWORK_CONFIG_FILE=$1
      shift;;
    *)
      ARGS = "$ARGS $arg"
  esac
done

IP_ADDRESS=$IP_ADDRESS_BASE$HOST_NUMBER
echo "IP_ADDRESSS=$IP_ADDRESS"
echo "MASK=$MASK"
echo "NETWORK_CONFIG_FILE=$NETWORK_CONFIG_FILE"

echo "# This file describes the network interfaces available on your system
# and how to activate them. For more information, see interfaces(5).

source /etc/network/interfaces.d/*

# The loopback network interface
auto lo
iface lo inet loopback

# The primary network interface
auto enp0s3
iface enp0s3 inet dhcp

# The virtual host adapter interface
auto enp0s8
iface enp0s8 inet static
address $IP_ADDRESS
netmask $MASK" > $NETWORK_CONFIG_FILE
