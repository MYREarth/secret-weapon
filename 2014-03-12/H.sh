#!/bin/bash
count=0
while true; do
    count=$(($count+ 1))
    echo Test \#$count
    if ! python H.py > H2.in; then
        break;
    fi
    ./H < H2.in > H.out
    ./H2 < H2.in > H2.out
    if diff H.out H2.out; then
        echo OK!
    else
        echo WA WA WA!
        break
    fi
done
