#!/bin/bash

./init &
PID3=$!
sleep 3
./capture &
PID=$!
./convert &
PID1=$!
./draw
PID2=$!
#chrt -p $PID
#chrt -p $PID1
#chrt -p $PID2