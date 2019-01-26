#!/bin/bash
IP_ADDRESS_BASE="192.168.56"
for FIRST_HOST in $IP_ADDRESS_BASE.10{0..3}; do
  # echo $FIRST_HOST parallel-ssh -i $(echo "-H $IP_ADDRESS_BASE".10{0..3} | sed -e 's/'"-H $FIRST_HOST"'//g') hostname -I
  ssh $FIRST_HOST parallel-ssh -i $(echo "-H $IP_ADDRESS_BASE".10{0..3} | sed -e 's/'"-H $FIRST_HOST"'//g') hostname -I
done
