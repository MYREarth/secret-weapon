#!/bin/bash
count=0
while true; do
    count=$(($count + 1))
    if ! python2 P.py $@ > P.in; then
        break
    fi
    ./P < P.in > P.out
    ./p < P.in > p.out
    if diff p.out P.out; then
        echo OK
    else
        echo WA
        break
    fi
done
