#!/bin/bash

nohup wine beatvs.exe run --ip 127.0.0.1 --port 9485 2>&1 & 

nohup ./HiData.Sync run --port 81 > ./sync.log  &

./beat-vs $@
