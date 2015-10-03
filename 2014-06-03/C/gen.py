from random import randint

T = 10000
print T
for _ in xrange(T):
    print " ".join(map(str, sorted([randint(1, 10 ** 18), randint(1, 10 ** 18)])))

