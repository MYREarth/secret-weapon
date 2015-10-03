make B
echo "" > B.out2
for n in `seq 2 150`; do
    echo $n
    echo $n | ./B >> b.cpp
done
