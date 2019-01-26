#!/bin/sh -eox
ssh siri3us@192.168.56.100 parallel-ssh -i -H 192.168.56.101 -H 192.168.56.102 -H 192.168.56.103 hostname -I
ssh siri3us@192.168.56.101 parallel-ssh -i -H 192.168.56.100 -H 192.168.56.102 -H 192.168.56.103 hostname -I
ssh siri3us@192.168.56.102 parallel-ssh -i -H 192.168.56.100 -H 192.168.56.101 -H 192.168.56.103 hostname -I
ssh siri3us@192.168.56.103 parallel-ssh -i -H 192.168.56.100 -H 192.168.56.101 -H 192.168.56.102 hostname -I
