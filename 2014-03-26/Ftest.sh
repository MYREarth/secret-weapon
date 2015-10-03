#!/bin/bash
make F
make Fbf
while true; do
    if ! python2 Fgen.py $@ > F.in; then
        break
    fi
    ./F < F.in > F.out
    ./Fbf < F.in > Fbf.out
    if diff F.out Fbf.out; then
        echo OK
    else
        echo WA!
        break
    fi
done
