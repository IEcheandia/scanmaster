#!/bin/bash

for g in /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
do
    echo performance > $g
done

