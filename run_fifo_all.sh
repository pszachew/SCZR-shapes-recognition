#!/bin/bash

./init &
PID=$!
chrt -p -f 99 $PID

./capture &
PID1=$!
chrt -p -f 99 $PID1

./convert &
PID2=$!
chrt -p -f 99 $PID2

./draw &
PID3=$!
chrt -p -f 99 $PID3

chrt -p $PID
chrt -p $PID
chrt -p $PID
chrt -p $PID
