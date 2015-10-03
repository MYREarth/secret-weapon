from random import randint
N = 100000
print N
for i in xrange(N):
    print i, i + 1, randint(0, 10 ** 9), randint(0, 10 ** 9)
