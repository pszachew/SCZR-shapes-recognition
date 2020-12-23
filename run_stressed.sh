#!/bin/bash

./init &
PID=$!
./capture &
PID1=$!

./convert &
PID2=$!

./draw &
PID3=$!

chrt -p $PID
chrt -p $PID1
chrt -p $PID2
chrt -p $PID3

(stress-ng --cpu 256 --vm 256 --timer 256 --timeout 60s) &
