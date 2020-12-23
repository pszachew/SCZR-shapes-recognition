#!/bin/bash

./destroyer

./init &
PID=$!
./capture &
PID1=$!
./convert &
PID2=$!
./draw &
PID3=$!
chrt -p $PID1
chrt -p $PID2
chrt -p $PID3

# python3 ./plots.py build/delays.log