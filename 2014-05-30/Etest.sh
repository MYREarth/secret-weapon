#!/bin/bash
test_count=0
make E
while true; do
    test_count=$(($test_count + 1))
    echo Test \#$test_count
    python2 Egen.py $@ > E1.in
    ./E < E1.in > E1.out
    python2 Eeval.py < E1.out > E1.out.out
    python2 E.py < E1.in > E2.out
    python2 Eeval.py < E2.out > E2.out.out
    if diff E1.out.out E2.out.out; then
        echo OK
    else
        echo Congraulations!
        break
    fi
done
