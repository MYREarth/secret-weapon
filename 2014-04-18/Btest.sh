#!/usr/bin/env bash
count=0
while true; do
    count=$(($count + 1))
    if ! python2 Bgen.py $@ > b.in; then
        break;
    fi
    ./B < b.in > b.out
    if ! python2 Bbf.py < b.in > b.ans; then
        break;
    fi
    if diff b.out b.ans; then
        echo OK!
    else
        echo WA
        break
    fi
done
