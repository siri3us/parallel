#!/bin/bash

USER=$(whoami)  # User, which is running a script
IP_ADDRESS_BASE="192.168.56"
SSH_KEY_PATH="$HOME/.ssh/id_rsa_slave"

for HOST_NUMBER in {0..3}; do
  FULL_HOST_ADDRESS=$USER@$IP_ADDRESS_BASE.10$HOST_NUMBER
  echo "Adding public slave ssh-key to the \"~/.ssh/authorized_keys\" of $FULL_HOST_ADDRESS"
  ssh-copy-id -i $SSH_KEY_PATH $FULL_HOST_ADDRESS
  if [ $? -ne 0 ]; then
    # Maximum HOST_NUMBER has been reached
    break
  fi

  echo "Adding private slave ssh-key to the \"~/.ssh\" of $FULL_HOST_ADDRESS"
  scp $SSH_KEY_PATH $FULL_HOST_ADDRESS:~/.ssh/id_rsa
done

HOST_NUMBER=$((HOST_NUMBER-1))
echo "Host number range is: 0..$HOST_NUMBER"
