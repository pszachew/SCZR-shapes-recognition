#!/bin/bash

./init &
sleep 5
./capture &
PID=$!
sleep 1
./convert &
PID1=$!
sleep 1
./draw
PID2=$!

chrt -p $PID
chrt -p $PID1
chrt -p $PID2