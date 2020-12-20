#!/bin/bash

./init &
sleep 1
./capture &
sleep 1
./convert &
sleep 1
./draw

