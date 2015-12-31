#!/bin/sh

for nchan in 1 2 4
do
    echo "${nchan} channels"
    for trial in {0..2}
    do
        ./emulator-Top-Benchmark${nchan}ChannelConfig +dramsim pk membw
    done
done
