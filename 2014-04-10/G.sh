#!/bin/bash
count=0
while true; do
    count=$(($count + 1))
    if ! python2 G.py $@ > G.in; then
        break
    fi
    ./G  < G.in > G.out
    ./G2 < G.in > G2.out
    if diff G.out G2.out; then
        echo OK
    else
        echo WA!
        break
    fi
done
