#!/bin/bash

USER=$(whoami)  # User, which is running a script
IP_ADDRESS_BASE="192.168.56.1"
SSH_KEY_PATH="~/.ssh/id_rsa_slave"

for HOST_NUMBER in {0..9}; do
  echo "Adding public slave ssh-key to the \"~/.ssh/authorized_keys\" of $USER@$IP_ADDRESS_BASE.$HOST_NUMBER"
  ssh-copy-id -i $SSH_KEY_PATH $USER@$IP_ADDRESS_BASE.$HOST_NUMBER
  if [ $? -ne 0 ]; then
    # Maximum HOST_NUMBER has been reached
    break
  fi

  echo "Adding private slave ssh-key to the \"~/.ssh\" of $USER@$IP_ADDRESS_BASE.$HOST_NUMBER"
  scp $SSH_KEY_PATH $USER@$IP_ADDRESS_BASE.$HOST_NUMBER:~/.ssh/
done

HOST_NUMBER=$((HOST_NUMBER-1))
echo "Host number range is: 0..$HOST_NUMBER"
