#!/bin/bash
chmod +x start.sh beatvs.exe beat-vs HiData.Sync
docker build -f Dockerfile -t hidata/beat-vs:v2.1.0 .
